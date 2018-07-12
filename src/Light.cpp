//
// Created by luca on 24/06/18.
//

#include "Light.h"

Light::Light(Geometry *geometry, glm::vec3 color, float intensity) {
	this->geometry = geometry;
	this->color = color;
	this->intensity = intensity;
}

glm::vec3 Light::randomPoint() {
	//return this->geometry.randomPoint();
}


