//
// Created by luca on 23/07/18.
//

#ifndef CG_PATH_TRACER_SPHEREGEOMETRY_H
#define CG_PATH_TRACER_SPHEREGEOMETRY_H


#include "Geometry.h"

class SphereGeometry : public Geometry {
	public:

	glm::vec3 position;
	float r;

	SphereGeometry(glm::vec3 position, float r);

	std::string toString() override;

	ObjectIntersection intersect(const Ray& ray) override;

	glm::vec3 randomPoint() override;
};


#endif //CG_PATH_TRACER_SPHEREGEOMETRY_H
