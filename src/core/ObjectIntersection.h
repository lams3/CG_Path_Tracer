//
// Created by luca on 29/06/18.
//

#ifndef CG_PATH_TRACER_OBJECTINTERSECTION_H
#define CG_PATH_TRACER_OBJECTINTERSECTION_H

#include "../../dependencies/glm/glm.hpp"
#include "Material.h"
#include "../geometry/VertexData.h"

//TODO t, geometry, material, TBN

class ObjectIntersection {
	public:
	static const ObjectIntersection EMPTY;

	float t;
	VertexData v;
	glm::mat3 TBN;
	Material* material;

	ObjectIntersection(float t, VertexData v, glm::mat3 TBN, Material* m);

	glm::vec3 shadeNormal();

	glm::vec3 shadeColor();

	glm::vec3 shadePosition();

};


#endif //CG_PATH_TRACER_OBJECTINTERSECTION_H
