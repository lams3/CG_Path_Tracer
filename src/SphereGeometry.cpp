//
// Created by luca on 23/07/18.
//

#include "SphereGeometry.h"

std::string SphereGeometry::toString() {
	return "not implemented";
}

ObjectIntersection SphereGeometry::intersect(const Ray &ray) {
	glm::vec3 op = ray.origin - this->position;

	float a = 1;
	float b = 2.0f * glm::dot(ray.direction, op);
	float c = glm::dot(op, op) - r * r;
	float delta = b * b - 4 * a * c;

	if (delta < 0.001f)
		return ObjectIntersection(-1.0f, glm::vec3(0.0f), glm::vec3(0.0f), nullptr);

	float sDelta = sqrtf(delta);

	float t1 = (-b - sDelta) / 2.0f;
	float t2 = (-b + sDelta) / 2.0f;

	float t;
	if (t1 >= ray.minDistance)
		t = t1;
	else if (t2 >= ray.minDistance)
		t = t2;
	else t = -1;

	glm::vec3 position = ray.origin + t * ray.direction;
	return ObjectIntersection(t, position, glm::normalize(position - this->position), nullptr);
}

glm::vec3 SphereGeometry::randomPoint() {
	return glm::vec3();
}

SphereGeometry::SphereGeometry(glm::vec3 position, float r) {
	this->position = position;
	this->r = r;
}
