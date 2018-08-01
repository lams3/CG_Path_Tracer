//
// Created by luca on 29/07/18.
//

#include "BoxGeometry.h"

glm::vec3 BoxGeometry::randomPoint() {
	glm::vec3 lerp(
			(float) rand() / (float) RAND_MAX,
			(float) rand() / (float) RAND_MAX,
			(float) rand() / (float) RAND_MAX
	);
	return glm::vec3(
			(1.0f - lerp.x) * this->min.x + lerp.x * this->max.x,
			(1.0f - lerp.y) * this->min.y + lerp.y * this->max.y,
			(1.0f - lerp.z) * this->min.z + lerp.z * this->max.z
	);
}

ObjectIntersection BoxGeometry::intersect(const Ray &ray) {
	glm::vec3 min = this->min;
	glm::vec3 max = this->max;
	glm::vec3 o = ray.getOrigin();
	glm::vec3 d = ray.getDirection();

	float tmin = (min.x - o.x) / d.x;
	float tmax = (max.x - o.x) / d.x;

	if (tmin > tmax)
		std::swap(tmin, tmax);

	float tymin = (min.y - o.y) / d.y;
	float tymax = (max.y - o.y) / d.y;

	if (tymin > tymax)
		std::swap(tymin, tymax);

	if ((tmin > tymax) || (tymin > tmax))
		ObjectIntersection::EMPTY;

	if (tymin > tmin)
		tmin = tymin;

	if (tymax < tmax)
		tmax = tymax;

	float tzmin = (min.z - o.z) / d.z;
	float tzmax = (max.z - o.z) / d.z;

	if (tzmin > tzmax)
		std::swap(tzmin, tzmax);

	if ((tmin > tzmax) || (tzmin > tmax))
		return ObjectIntersection::EMPTY;

	if (tzmin > tmin)
		tmin = tzmin;

	if (tzmax < tmax)
		tmax = tzmax;

	return ObjectIntersection(tmin, VertexData(ray.sample(tmin), glm::vec3(), glm::vec2()), glm::mat3(), nullptr);
}

BoxGeometry::BoxGeometry(glm::vec3 min, glm::vec3 max) {
	this->min = min;
	this->max = max;
}
