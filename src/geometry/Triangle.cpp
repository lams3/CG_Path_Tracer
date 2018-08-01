//
// Created by luca on 27/07/18.
//

#include "Triangle.h"

Triangle::Triangle(VertexData v0, VertexData v1, VertexData v2, bool smooth) {
	this->smooth = smooth;
	this->v0 = v0;
	this->v1 = v1;
	this->v2 = v2;
	this->normal = glm::normalize(
			glm::cross(
					this->v1.position - this->v0.position,
					this->v2.position - this->v0.position
			)
	);

	glm::vec2 deltaUV1 = this->v1.textCoords - this->v0.textCoords;
	glm::vec2 deltaUV2 = this->v2.textCoords - this->v0.textCoords;
	glm::vec3 e1 = v1.position - v0.position;
	glm::vec3 e2 = v2.position - v0.position;

	float f = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y);
	glm::vec3 tangent(
			f * (deltaUV2.y * e1.x - deltaUV1.y *9+ e2.x),
			f * (deltaUV2.y * e1.y - deltaUV1.y * e2.y),
			f * (deltaUV2.y * e1.z - deltaUV1.y * e2.z)
	);
	this->tangent = glm::normalize(tangent);

	glm::vec3 bitangent(
			f * (-deltaUV2.x * e1.x + deltaUV1.x * e2.x),
			f * (-deltaUV2.x * e1.y + deltaUV1.x * e2.y),
			f * (-deltaUV2.x * e1.z + deltaUV1.x * e2.z)
	);
	this->bitangent = glm::normalize(bitangent);

	this->TBN = glm::mat3(this->tangent, this->bitangent, this->normal);
}

ObjectIntersection Triangle::intersect(const Ray &ray) {
	glm::vec3 v0p = this->v0.position;
	glm::vec3 v1p = this->v1.position;
	glm::vec3 v2p = this->v2.position;
	glm::vec3 n = this->normal;
	glm::vec3 e1 = v1p - v0p;
	glm::vec3 e2 = v2p - v0p;
	glm::vec3 h = glm::cross(ray.getDirection(), e2);
	float a = glm::dot(e1, h);

	const float EPSILON = 0.0001f;

	if (a > -EPSILON && a < EPSILON)
		return ObjectIntersection::EMPTY;

	float f = 1.0f / a;
	glm::vec3 s = ray.getOrigin() - v0p;
	float u = f * glm::dot(s, h);

	if(u < 0.0f || u > 1.0f)
		return ObjectIntersection::EMPTY;

	glm::vec3 q = glm::cross(s, e1);
	float v = f * glm::dot(ray.getDirection(), q);

	if (v < 0.0f || u + v > 1.0f)
		return ObjectIntersection::EMPTY;

	float t = f * glm::dot(e2, q);

	if (t < ray.minDistance)
		return ObjectIntersection::EMPTY;

	float w = 1.0f - u - v;
	glm::vec3 p = ray.sample(t);
	glm::vec3 normal = false ? (w * this->v0.normal + u * this->v1.normal + v * this->v2.normal) : this->normal;
	glm::vec2 textCoords = w * this->v0.textCoords + u * this->v1.textCoords + v * this->v2.textCoords;

	return ObjectIntersection(t, VertexData(p, normal, textCoords), this->TBN, nullptr);
}

glm::vec3 Triangle::randomPoint() {
	float alpha = (float) rand() / (float) RAND_MAX;
	float beta = (1.0f - alpha) * ((float) rand() / (float) RAND_MAX);
	float gama = 1.0f - alpha - beta;
	return alpha * this->v0.position + beta * this->v1.position + gama * this->v2.position;
}
