//
// Created by luca on 25/06/18.
//

#include <sstream>
#include <iostream>
#include <climits>
#include "MeshGeometry.h"
#include "SphereGeometry.h"

MeshGeometry::MeshGeometry(std::vector<glm::vec3> &vertices, std::vector<glm::ivec3> &faces, std::vector<glm::vec3>& normals) {
    this->vertices = std::move(vertices);
    this->faces = std::move(faces);
    this->normals = std::move(normals);
	this->computeBoundingGeometry();
}

MeshGeometry::MeshGeometry(const float radius, const glm::vec3& center, int segments)
{
	segments = segments > 3 ? segments : 3;
	const int s = segments + 1;
	std::vector<glm::vec3> vert;
	std::vector<glm::ivec3> face;
	std::vector<glm::vec3> norm;


	glm::vec3 p = glm::vec3(0.0f, -1.0f, 0.0f);
	vert.push_back(center + p * radius);
	norm.push_back(p);
	for (unsigned int i = 1; i < segments; i++) {
		for (unsigned int j = 0; j < segments; j++) {
			float theta = float(i * M_PI / segments);
			float phi = float(j * 2.0f * M_PI / segments);
			p = glm::vec3(-sin(theta)*cos(phi), -cos(theta), -sin(theta)*sin(phi));
			vert.push_back(center + p * radius);
			norm.push_back(p);
		}
	}
	p = glm::vec3(0.0f, 1.0f, 0.0f);
	vert.push_back(center + p * radius);
	norm.push_back(p);


	for (unsigned int i = 0; i < segments; i++)
	{
		face.push_back(glm::ivec3(0, (i + 1)%segments + 1, i + 1));
	}
	for (unsigned int i = 0; i < segments; i++) {
		for (unsigned int j = 0; j < segments - 2; j++) {
			face.push_back(glm::ivec3(i + 1 + j*segments, (i+1)%segments + 1 + (j+1)*segments, (i+1)%segments + 1 + j*segments));
			face.push_back(glm::ivec3(i + 1 + j*segments, i+1 + (j+1)*segments, (i+1)%segments + 1 + (j+1)*segments));
		}
	}
	for (unsigned int i = 0; i < segments; i++)
	{
		face.push_back(glm::ivec3(segments*(segments - 1) + 1, (i+1)%segments + 1 + (segments-2)*segments, i+1 + (segments-2)*segments));
	}
	this->vertices = vert;
	this->faces = face;
	this->normals = norm;
	this->computeBoundingGeometry();
}

std::string MeshGeometry::toString() {
    std::ostringstream ss;
    ss << "Vertices: " << std::endl;
    for (const auto& vertex : this->vertices)
        ss << "vertex " << vertex.x << " " << vertex.y << " " << vertex.z << std::endl;
    for (const auto& face : this->faces)
        ss << "face " << face.x << " " << face.y << " " << face.z << std::endl;
    return ss.str();
}

ObjectIntersection MeshGeometry::intersect(const Ray &ray) {
	ObjectIntersection bbItsc = this->boundingGeometry->intersect(ray);
	if (bbItsc.t == -1)
		return bbItsc;

    float tMin = -1;
    glm::ivec3 tMinFace;

    for (const auto& face : faces) {
        glm::vec3 v0 = this->vertices[face.x];
        glm::vec3 v1 = this->vertices[face.y];
        glm::vec3 v2 = this->vertices[face.z];
        glm::vec3 n = glm::normalize(glm::cross(v1 - v0, v2 - v0));
        glm::vec3 e1 = v1 - v0;
        glm::vec3 e2 = v2 - v0;
        glm::vec3 h = glm::cross(ray.direction, e2);
        float a = glm::dot(e1, h);

        const float EPSILON = 0.0001f;

        if (a > -EPSILON && a < EPSILON)
	        continue;

        float f = 1.0f / a;
        glm::vec3 s = ray.origin - v0;
        float u = f * glm::dot(s, h);

        if(u < 0.0f || u > 1.0f)
            continue;

        glm::vec3 q = glm::cross(s, e1);
        float v = f * glm::dot(ray.direction, q);

        if (v < 0.0f || u + v > 1.0f)
	        continue;

        float t = f * glm::dot(e2, q);

        if (t < ray.minDistance)
            continue;

	    if (tMin == -1 || t < tMin) {
            tMin = t;
            tMinFace = face;
        }
     }

    if (tMin == -1)
        return ObjectIntersection(-1, glm::vec3(), glm::vec3(), nullptr);

    glm::vec3 position = ray.origin + tMin * ray.direction;
	glm::vec3 v0 = this->vertices[tMinFace.x];
	glm::vec3 v1 = this->vertices[tMinFace.y];
	glm::vec3 v2 = this->vertices[tMinFace.z];
	/*float u, v, w;
	barycentric(position, v0, v1, v2, u, v, w);
    glm::vec3 n0 = this->normals[tMinFace.x];
    glm::vec3 n1 = this->normals[tMinFace.y];
    glm::vec3 n2 = this->normals[tMinFace.z];
    glm::vec3 normal = glm::normalize((u * n0) + (v * n1) + (w * n2));*/
	glm::vec3 normal = glm::normalize(glm::cross(v1 - v0, v2 - v0)) ;
	return ObjectIntersection(tMin, position, normal, nullptr);
}

void MeshGeometry::barycentric(glm::vec3 p, glm::vec3 a, glm::vec3 b, glm::vec3 c, float &u, float &v, float &w) {
	glm::vec3 crossABC = glm::cross(b - a, c - a);
	glm::vec3 crossPBC = glm::cross(b - p, c - p);
	glm::vec3 crossPCA = glm::cross(c - p, a - p);
	glm::vec3 normal = glm::normalize(crossABC);
	float areaABC = glm::dot(normal, crossABC);
	float areaPBC = glm::dot(normal, crossPBC);
	float areaPCA = glm::dot(normal, crossPCA);
	u = areaPBC / areaABC ; // alpha
	v = areaPCA / areaABC ; // beta
	w = 1.0f - u - v ; // gamma
}

glm::vec3 MeshGeometry::randomPoint() {
	glm::ivec3 face = this->faces[random() % this->faces.size()];
	float alpha = (float) rand() / (float) INT_MAX;
	float beta = (1.0f - alpha) * ((float) rand() / (float) INT_MAX);
	float gama = 1.0f - alpha - beta;
	return alpha * this->vertices[face.x] + beta * this->vertices[face.y] + gama * this->vertices[face.z];
}

void MeshGeometry::computeBoundingGeometry() {
	glm::vec3 min = this->vertices[0];
	glm::vec3 max = this->vertices[0];
	for (const auto& v : this->vertices) {
		if (v.x < min.x) min.x = v.x;
		if (v.y < min.y) min.y = v.y;
		if (v.z < min.z) min.z = v.z;
		if (v.x > max.x) max.x = v.x;
		if (v.y > max.y) max.y = v.y;
		if (v.z > max.z) max.z = v.z;
	}
	glm::vec3 center = 0.5f * min + 0.5f * max;
	float r = 0.0f;
	for (const auto& v : vertices)
		if (glm::distance(v, center) > r)
			r = glm::distance(v, center);
	this->boundingGeometry = new SphereGeometry(center, r);
}

