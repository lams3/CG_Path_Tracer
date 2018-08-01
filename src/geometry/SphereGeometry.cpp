//
// Created by luca on 23/07/18.
//

#include "SphereGeometry.h"

ObjectIntersection SphereGeometry::intersect(const Ray &ray) {
	glm::vec3 op = ray.getOrigin() - this->position;

	float a = 1.0f;
	float b = glm::dot(ray.getDirection(), op);
	float c = glm::dot(op, op) - r * r;
	float delta = b * b - a * c;

	if (delta < 0.0f)
		return ObjectIntersection::EMPTY;

	float sDelta = sqrtf(delta);

	float t1 = (-b - sDelta);
	float t2 = (-b + sDelta);

	float t = t1 > ray.minDistance ? t1 : (t2 > ray.minDistance ? t2 : -1);

	if (t < ray.minDistance)
		return ObjectIntersection::EMPTY;


	glm::vec3 p = ray.sample(t);
	return ObjectIntersection(t, VertexData(p, p - this->position, glm::vec2()), glm::mat3(), nullptr);
}

glm::vec3 SphereGeometry::randomPoint() {
	glm::vec3 randomDir(
			(float) rand() / (float) RAND_MAX,
			(float) rand() / (float) RAND_MAX,
			(float) rand() / (float) RAND_MAX
	);
	return this->position + this->r * glm::normalize(randomDir);
}

SphereGeometry::SphereGeometry(glm::vec3 position, float r) {
	this->position = position;
	this->r = r;
}
