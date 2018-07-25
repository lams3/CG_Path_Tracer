//
// Created by luca on 23/07/18.
//

#include <iostream>
#include "SphereGeometry.h"

std::string SphereGeometry::toString() {
	return "not implemented";
}

ObjectIntersection SphereGeometry::intersect(const Ray &ray) {
	glm::vec3 op = ray.origin - this->position;

	float a = 1.0f;
	float b = glm::dot(ray.direction, op);
	float c = glm::dot(op, op) - r * r;
	float delta = b * b - a * c;

	if (delta < 0.0f)
		return ObjectIntersection(-1, glm::vec3(0.0f), glm::vec3(0.0f), nullptr);

	float sDelta = sqrtf(delta);

	float t1 = (-b - sDelta);
	float t2 = (-b + sDelta);

	float t = t1 > ray.minDistance ? t1 : (t2 > ray.minDistance ? t2 : -1);

	if (t > ray.minDistance) {
		glm::vec3 p = ray.origin + t * ray.direction;
		return ObjectIntersection(t, p, glm::normalize(p - this->position), nullptr);
	}

	return ObjectIntersection(-1, glm::vec3(), glm::vec3(), nullptr);

}

glm::vec3 SphereGeometry::randomPoint() {
	return glm::vec3();
}

SphereGeometry::SphereGeometry(glm::vec3 position, float r) {
	this->position = position;
	this->r = r;
}
