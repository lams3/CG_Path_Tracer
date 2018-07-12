//
// Created by luca on 25/06/18.
//

#include "Material.h"

std::string Material::toString() {
    return "not implemented";
}

Material *Material::makeLightMaterial(float intensity, glm::vec3 color) {
	Material* m = new Material;
	m->color = color;
	m->ks = intensity;
	m->light = true;
	return m;
}

Material *Material::makeObjectMaterial(float kd, float ks, float kt, glm::vec3 color) {
	Material* m = new Material;
	m->kd = kd;
	m->ks = ks;
	m->kt = kt;
	m->color = color;
	m->light = false;
	return m;
}
