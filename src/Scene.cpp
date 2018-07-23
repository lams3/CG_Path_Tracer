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

void Scene::addLight(Object3D* light) {
	this->lights.emplace_back(light);
}

std::vector<Camera *> Scene::getCameras() {

	return this->cameras;
}

std::vector<Object3D *> Scene::getObjects() {

	return this->objects;
}

std::vector<Object3D *> Scene::getLights() {

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
	}

	for (const auto &light : this->lights) {
		ObjectIntersection intersection = light->intersect(ray);
		if (closest.t == -1)
			closest = intersection;
		if (intersection.t > -1 && intersection.t < closest.t)
			closest = intersection;
	}

	return closest;
}

glm::vec3 Scene::trace(const Ray &ray, int depth) {

	ObjectIntersection closest = this->intersect(ray);

	if (closest.t == -1)
		return glm::vec3(0.0, 0.0, 0.0);

	if (closest.material->light)
		return closest.material->color;

	if (depth > 5)
		return glm::vec3(0.0f, 0.0f, 0.0f);

	glm::vec3 directIllumination(0.0, 0.0, 0.0);
	glm::vec3 v = glm::normalize(ray.origin - closest.position);
	glm::vec3 n = glm::normalize(closest.normal);
	n = glm::dot(n, v) >= 0 ? n : -n;
	for (const auto& light : this->lights) {
		glm::vec3 lp = light->randomPoint();
		glm::vec3 l = glm::normalize(lp - closest.position);
		ObjectIntersection lightPath = this->intersect(Ray(closest.position, l, 0.001));
		if (!lightPath.material->light)
			continue;
		glm::vec3 r = glm::normalize((2.0f * n * glm::dot(l, n)) - l);
		float ln = std::max(glm::dot(l, n), 0.0f);
		float rv = std::max(glm::dot(r, v), 0.0f);
		glm::vec3 diff = closest.material->kd * ln * closest.material->color * light->material->color;
		glm::vec3 spec(0.0, 0.0, 0.0);
		//glm::vec3 spec = closest.material->ks * rv * light->material->color;
		directIllumination += light->material->ks * (diff + spec);
	}


	glm::vec3 indirectIllumination(0.0f, 0.0f, 0.0f);
	float ktot = closest.material->kd + closest.material->ks + closest.material->kt;
	float randSelect = ktot * ((float) rand() / RAND_MAX);
	if (randSelect <= closest.material->kd) {
		float r1 = 2.0f * M_PI * (float) rand() / RAND_MAX;
		float r2 = (float) rand() / RAND_MAX;
		float r2s = sqrt(r2);
		glm::vec3 w1 = n;
		glm::vec3 u1 = glm::normalize(glm::cross(fabs(w1.x) >= 0.1 ? glm::vec3(0.0, 1.0, 0.0) : glm::vec3(1.0, 0.0, 0.0), w1));
		glm::vec3 v1 = glm::cross(w1, u1);
		glm::vec3 d1 = glm::normalize(u1*cosf(r1)*r2s + v1*sinf(r1)*r2s + w1*sqrtf(1.0f-r2));
		indirectIllumination += closest.material->kd * glm::dot(n, d1) * this->trace(Ray(closest.position, d1, 0.001), depth + 1);
	} else if (randSelect <= (closest.material->kd + closest.material->ks)) {
		glm::vec3 perfectReflection = glm::normalize((2.0f * n * glm::dot(v, n)) - v);
		indirectIllumination += closest.material->ks * closest.material->color * this->trace(Ray(closest.position, perfectReflection, 0.001), depth + 1);
	} else {
		indirectIllumination += closest.material->kt * closest.material->color * this->trace(Ray(closest.position, ray.direction, 0.001), depth + 1);
	}

	return directIllumination + closest.material->color * indirectIllumination;
}
