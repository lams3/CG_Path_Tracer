//
// Created by luca on 25/06/18.
//

#ifndef CG_PATH_TRACER_MATERIAL_H
#define CG_PATH_TRACER_MATERIAL_H


#include <string>
#include <glm/glm.hpp>

class Material {
	public:

	float kd, ks, kt;
	bool light;
	glm::vec3 color;

	static Material* makeLightMaterial(float intensity, glm::vec3 color);

	static Material* makeObjectMaterial(float kd, float ks, float kt, glm::vec3 color);

    virtual std::string toString();
};


#endif //CG_PATH_TRACER_MATERIAL_H
