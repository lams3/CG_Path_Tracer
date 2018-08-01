//
// Created by luca on 29/07/18.
//

#ifndef CG_PATH_TRACER_BOXGEOMETRY_H
#define CG_PATH_TRACER_BOXGEOMETRY_H


#include "Geometry.h"

class BoxGeometry : public Geometry {
	public:
	glm::vec3 min;
	glm::vec3 max;

	BoxGeometry(glm::vec3 min, glm::vec3 max);

	ObjectIntersection intersect(const Ray& ray) override;

	glm::vec3 randomPoint() override;
};


#endif //CG_PATH_TRACER_BOXGEOMETRY_H
