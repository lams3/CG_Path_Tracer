//
// Created by luca on 25/06/18.
//

#include "Material.h"

Material *Material::makeLightMaterial(float intensity, glm::vec3 color) {
	auto * m = new Material;
	m->color = color;
	m->ks = intensity;
	m->light = true;
	m->displacementMap.active = false;
	m->normalMap.active = false;
	m->diffuseMap.active = false;
	return m;
}
