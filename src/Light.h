//
// Created by luca on 24/06/18.
//

#ifndef CG_PATH_TRACER_LIGHT_H
#define CG_PATH_TRACER_LIGHT_H


#include "Object3D.h"

class Light {
	public:
	Geometry* geometry;
	glm::vec3 color;
	float intensity;

	Light(Geometry* geometry, glm::vec3 color, float intensity);

	glm::vec3 randomPoint();
};


#endif //CG_PATH_TRACER_LIGHT_H
