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

	glm::vec3 p = closest.position;
	glm::vec3 v = -ray.direction;
	glm::vec3 n = closest.normal;
	glm::vec3 n2 = glm::dot(n, v) >= 0 ? n : -n;

	glm::vec3 directIllumination(0.0f, 0.0f, 0.0f);
	for (const auto& light : this->lights) {
		glm::vec3 lp = light->randomPoint();
		glm::vec3 l = glm::normalize(lp - p);
		ObjectIntersection lightPath = this->intersect(Ray(p, l, 0.001));
		if (!lightPath.material->light) //TODO multiple lights
			continue;

		float diff = glm::dot(n2, l);
		if (diff <= 0.0f)
			continue;

		float il = light->material->ks;
		directIllumination += il * closest.material->kd * diff * light->material->color * closest.material->color;

		glm::vec3 r = (2.0f * (l * n2) * n2) - l;
		float spec = glm::dot(r, v);
		if (spec <= 0.0f)
			continue;

		//directIllumination += il * closest.material->ks * spec * light->material->color;
	}

	glm::vec3 indirectIllumination(0.0f, 0.0f, 0.0f);
	float ktot = closest.material->kd + closest.material->ks + closest.material->kt;
	float randSelect = ktot * ((float) rand() / RAND_MAX);
	if (randSelect <= closest.material->kd) {
		float r1 = 2.0f * M_PI * (float) rand() / RAND_MAX;
		float r2 = (float) rand() / RAND_MAX;
		float r2s = sqrt(r2);
		glm::vec3 w1 = n2;
		glm::vec3 u1 = glm::normalize(glm::cross(fabs(w1.x) > fabs(w1.y) ? glm::vec3(0.0, 1.0, 0.0) : glm::vec3(1.0, 0.0, 0.0), w1));
		glm::vec3 v1 = glm::cross(w1, u1);
		//glm::vec3 d1 = glm::normalize(v1*r2s*cosf(r1) + w1*sqrtf(1.0f - r2) + u1*r2s*sinf(r1));
		glm::vec3 d1 = v1*r2s*cosf(r1) + w1*sqrtf(1.0f - r2) + u1*r2s*sinf(r1);
		indirectIllumination = closest.material->kd * glm::dot(n, d1) * closest.material->color * this->trace(Ray(closest.position, d1, 0.001), depth + 1);
	} else if (randSelect <= (closest.material->kd + closest.material->ks)) {
		glm::vec3 perfectReflection = (2.0f * n2 * glm::dot(v, n2)) - v;
		indirectIllumination = closest.material->ks * this->trace(Ray(closest.position, perfectReflection, 0.001), depth + 1);
	} else {
		float m1 = 1.0f;
		float m2 = 1.3f;
		float cosT1;
		float cosT2;
		float rf;

		rf = (m1 / m2);
		cosT1 = glm::dot(n, v);
		cosT2 = sqrtf(1 - rf * rf * (1 - cosT1 * cosT1));
		cosT2 = cosT1 >= 0.0f ? cosT2 : -cosT2;
		glm::vec3 refract = glm::normalize((rf * ray.direction) + (rf * cosT1 - cosT2) * n);
		indirectIllumination = closest.material->kt * this->trace(Ray(closest.position, refract, 0.001), depth + 1);
	}

	return directIllumination + indirectIllumination;
}
