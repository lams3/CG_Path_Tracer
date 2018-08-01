//
// Created by luca on 24/06/18.
//

#include <iostream>
#include "Scene.h"

Scene::Scene() = default;

void Scene::addCamera(Camera *camera) {
	this->cameras.push_back(camera);
}

void Scene::addObject(Object3D *object) {
	this->objects.push_back(object);
}

void Scene::addLight(Object3D* light) {
	this->lights.push_back(light);
}

std::vector<Camera*> Scene::getCameras() {
	return this->cameras;
}

std::vector<Object3D*> Scene::getObjects() {
	return this->objects;
}

std::vector<Object3D*> Scene::getLights() {
	return this->lights;
}

ObjectIntersection Scene::intersect(const Ray& ray) {
	ObjectIntersection closest = ObjectIntersection::EMPTY;

	for (const auto &object : this->objects) {
		ObjectIntersection intersection = object->intersect(ray);

		if (intersection.t == -1)
			continue;

		if (closest.t == -1 || intersection.t < closest.t)
			closest = intersection;
	}

	for (const auto &light : this->lights) {
		ObjectIntersection intersection = light->intersect(ray);

		if (intersection.t == -1)
			continue;

		if (closest.t == -1 || intersection.t < closest.t)
			closest = intersection;
	}

	return closest;
}

glm::vec3 Scene::trace(const Ray &ray, int depth, glm::vec3 attenuation) {

	ObjectIntersection closest = this->intersect(ray);

	if (closest.t == -1)
		return glm::vec3(0.0, 0.0, 0.0);

	if (closest.material->light)
		return closest.material->color;

	if (attenuation.x <= 0.05 && attenuation.y <= 0.05 && attenuation.z <= 0.05)
		return glm::vec3(0.0, 0.0, 0.0);

	if (depth > 15)
		return glm::vec3(0.0, 0.0, 0.0);

	//glm::vec3 p = closest.position;
	glm::vec3 p = closest.shadePosition();
	glm::vec3 v = -ray.getDirection();
	//glm::vec3 n = closest.normal;
	glm::vec3 n = closest.shadeNormal();
	glm::vec3 n2 = glm::dot(n, v) > 0.0 ? n : -n;
	//glm::vec3 color = closest.color;
	glm::vec3 color = closest.shadeColor();
	glm::vec3 directIllumination(0.0, 0.0, 0.0);
	glm::vec3 indirectIllumination(0.0f, 0.0f, 0.0f);

	float ktot = closest.material->kd + closest.material->ks + closest.material->kt;
	float randSelect = ktot * ((float) rand() / RAND_MAX);
	if (randSelect < closest.material->kd) {
		for (const auto& light : this->lights) {
			glm::vec3 lp = light->randomPoint();
			glm::vec3 l = glm::normalize(lp - p);

			ObjectIntersection lightPath = this->intersect(Ray(p, l, 0.001));

			if (lightPath.material != light->material)
				continue;

			float diff = glm::dot(n2, l);
			if (diff <= 0.0f)
				continue;

			float il = light->material->ks;
			directIllumination += il * closest.material->kd * diff * light->material->color * color;

			glm::vec3 r = (2.0f * (l * n2) * n2) - l;
			float spec = glm::dot(r, v);
			if (spec <= 0.0f)
				continue;

			spec = powf(spec, closest.material->n);

			directIllumination += il * closest.material->ks * spec * light->material->color;
		}

		float r1 = float(2.0f * M_PI * rand() / RAND_MAX);
		float r2 = (float) rand() / RAND_MAX;
		float r2s = sqrtf(r2);
		glm::vec3 w1 = n2;
		glm::vec3 u1 = glm::normalize(glm::cross(fabs(w1.x) > fabs(w1.y) ? glm::vec3(0.0, 1.0, 0.0) : glm::vec3(1.0, 0.0, 0.0), w1));
		glm::vec3 v1 = glm::cross(w1, u1);
		glm::vec3 d1 = v1*r2s*cosf(r1) + w1*sqrtf(1.0f - r2) + u1*r2s*sinf(r1);

		glm::vec3 diff = closest.material->kd * glm::dot(n2, d1) * color;
		indirectIllumination = diff * this->trace(Ray(p, d1, 0.001), depth + 1, diff * attenuation);
	} else if (randSelect < (closest.material->kd + closest.material->ks)) {
		//TODO specular cone
		glm::vec3 perfectReflection = (2.0f * glm::dot(v, n2) * n2) - v;
		glm::vec3 spec = color;
		indirectIllumination = spec * this->trace(Ray(p, perfectReflection, 0.001), depth + 1, spec * attenuation);
	} else {
		float m1 = 1.0f;
		float m2 = closest.material->kr;
		float cosT1;
		float cosT2;
		float rf;
		rf = (m1 / m2);
		cosT1 = glm::dot(n, v);
		cosT2 = sqrtf(1 - rf * rf * (1 - cosT1 * cosT1));
		cosT2 = cosT1 >= 0.0f ? cosT2 : -cosT2;
		glm::vec3 refract = glm::normalize((rf * ray.getDirection()) + (rf * cosT1 - cosT2) * n);
		glm::vec3 trans = color;
		indirectIllumination = trans * this->trace(Ray(p, refract, 0.001), depth + 1, trans * attenuation);
	}

	return directIllumination + indirectIllumination;
}
