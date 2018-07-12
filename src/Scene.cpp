//
// Created by luca on 24/06/18.
//

#include <iostream>
#include "Scene.h"

Scene::Scene() {

}

void Scene::add(Camera *camera) {

	this->cameras.emplace_back(camera);
}

void Scene::add(Object3D *object) {

	this->objects.emplace_back(object);
}

void Scene::add(Light *light) {

	this->lights.emplace_back(light);
}

std::vector<Camera *> Scene::getCameras() {

	return this->cameras;
}

std::vector<Object3D *> Scene::getObjects() {

	return this->objects;
}

std::vector<Light *> Scene::getLights() {

	return this->lights;
}

ObjectIntersection Scene::intersect(const Ray& ray) {
	ObjectIntersection closest(-1, glm::vec3(), glm::vec3(), nullptr);
	for (const auto &object : this->objects) {
		ObjectIntersection intersection = object->intersect(ray);
		if (closest.t == -1)
			closest = intersection;
		if (intersection.t > -1 && intersection.t < closest.t)
			closest = intersection;
		//return glm::vec3(1.0, 0.0, 0.0);
	}
	return closest;
}

glm::vec3 Scene::trace(const Ray &ray, int depth) {

	if (depth == 20)
		return glm::vec3(0.0, 0.0, 0.0);

	ObjectIntersection closest = this->intersect(ray);

	if (closest.t == -1)
		return glm::vec3(0.0, 0.0, 0.0);

	glm::vec3 l = glm::normalize(glm::vec3(0.0, 3.0, -24.90600) - closest.position);

	ObjectIntersection lightPath = this->intersect(Ray(closest.position, l, 0.001));

	if (glm::length(glm::vec3(0.0, 3.2, -24.90600) - closest.position) > lightPath.t && lightPath.t != -1)
		return glm::vec3(0.0, 0.0, 0.0);

	glm::vec3 n = glm::normalize(closest.normal);
	glm::vec3 r = glm::normalize((2.0f * n * (l * n)) - l);
	glm::vec3 v = glm::normalize(ray.origin - closest.position);
	float ln = std::max(glm::dot(l, n), 0.0f);
	float rv = std::max(glm::dot(r, v), 0.0f);
	glm::vec3 color = ln * glm::vec3(1.0, 0.0, 0.0) + 0.1f * rv * glm::vec3(1.0, 1.0, 1.0);
	return 0.5f * color;
}
