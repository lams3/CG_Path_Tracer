//
// Created by luca on 25/06/18.
//

#include <sstream>
#include <iostream>
#include <climits>
#include "MeshGeometry.h"
#include "SphereGeometry.h"
#include "BoxGeometry.h"

ObjectIntersection MeshGeometry::intersect(const Ray &ray) {
	ObjectIntersection bbItsc = this->boundingGeometry->intersect(ray);
	if (bbItsc.t == -1)
		return bbItsc;

	ObjectIntersection closest = ObjectIntersection::EMPTY;

	for (auto& face : triangles) {
		ObjectIntersection itsc = face.intersect(ray);

		if (itsc.t == -1)
			continue;

		if (closest.t == -1 || itsc.t < closest.t)
			closest = itsc;
	}

	return closest;
}

glm::vec3 MeshGeometry::randomPoint() {
	Triangle t = this->triangles[rand() % this->triangles.size()];
	return t.randomPoint();
}

void MeshGeometry::computeBoundingGeometry() {
	glm::vec3 min = this->triangles.front().v0.position;
	glm::vec3 max = min;
	for (const auto& t : this->triangles) {
		glm::vec3 vt[] = {
				t.v0.position,
				t.v1.position,
				t.v2.position
		};
		for (const auto& v : vt) {
			if (v.x < min.x) min.x = v.x;
			if (v.y < min.y) min.y = v.y;
			if (v.z < min.z) min.z = v.z;
			if (v.x > max.x) max.x = v.x;
			if (v.y > max.y) max.y = v.y;
			if (v.z > max.z) max.z = v.z;
		}
	}
	glm::vec3 center = 0.5f * min + 0.5f * max;
	float r = glm::distance(center, max);
	BoxGeometry* bg = new BoxGeometry(min, max);
	float bgv = (max.x - min.x) * (max.y - min.y) * (max.z - min.z);
	SphereGeometry* sg = new SphereGeometry(center, r);
	float sgv = float((4.0f / 3.0f) * M_PI * r * r * r);
	this->boundingGeometry = sgv <= bgv ? dynamic_cast<Geometry*>(sg) : dynamic_cast<Geometry*>(bg);
}

MeshGeometry::MeshGeometry(std::vector<Triangle>& triangles) {
	this->triangles = std::move(triangles);
	this->computeBoundingGeometry();
}

