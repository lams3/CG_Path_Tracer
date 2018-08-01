//
// Created by luca on 25/06/18.
//

#ifndef CG_PATH_TRACER_MATERIAL_H
#define CG_PATH_TRACER_MATERIAL_H


#include <string>
#include "../../dependencies/glm/glm.hpp"

struct Texture {
	bool active;
	unsigned char* data;
	int w, h, n;
	float max;
};

class Material {
	public:

	glm::vec3 color;
	float ka, kd, ks, kt, kr, n;
	bool light, smooth;
	Texture displacementMap;
	Texture normalMap;
	Texture diffuseMap;

	static Material* makeLightMaterial(float intensity, glm::vec3 color);
};


#endif //CG_PATH_TRACER_MATERIAL_H
