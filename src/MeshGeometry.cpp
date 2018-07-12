//
// Created by luca on 25/06/18.
//

#include <sstream>
#include <iostream>
#include <climits>
#include "MeshGeometry.h"

MeshGeometry::MeshGeometry(std::vector<glm::vec3> &vertices, std::vector<glm::ivec3> &faces, std::vector<glm::vec3>& normals) {
    this->vertices = std::move(vertices);
    this->faces = std::move(faces);
    this->normals = std::move(normals);
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
    float tMin = -1;
    glm::ivec3 tMinFace;

    for (const auto& face : faces) {
        glm::vec3 v0 = this->vertices[face.x];
        glm::vec3 v1 = this->vertices[face.y];
        glm::vec3 v2 = this->vertices[face.z];
        glm::vec3 n = glm::normalize(glm::cross(v1 - v0, v2 - v0));

        if (glm::dot(n, ray.direction) == 0.0f)
            continue;

	    float d = -glm::dot(n, v0);
	    float t = (- d - glm::dot(n, ray.origin)) / glm::dot(n, ray.direction);

        if (t < ray.minDistance)
            continue;

        glm::vec3 q = ray.origin + t * ray.direction;

	    float u, v, w;
	    u = dot(glm::cross(v1 - q, v2 - q), n);
	    v = dot(glm::cross(q - v0, v2 - v0), n);
	    w = dot(glm::cross(v1 - v0, q - v0), n);

	    if (u < 0 || v < 0 || w < 0) continue;

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
	float u, v, w;
	barycentric(position, v0, v1, v2, u, v, w);
    glm::vec3 n0 = this->normals[tMinFace.x];
    glm::vec3 n1 = this->normals[tMinFace.y];
    glm::vec3 n2 = this->normals[tMinFace.z];
    glm::vec3 normal = glm::normalize((u * n0) + (v * n1) + (w * n2));

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

