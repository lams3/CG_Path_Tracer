//
// Created by luca on 27/07/18.
//

#ifndef CG_PATH_TRACER_TRIANGLE_H
#define CG_PATH_TRACER_TRIANGLE_H

#include "../../dependencies/glm/glm.hpp"
#include "../core/ObjectIntersection.h"
#include "../core/Ray.h"
#include "Geometry.h"
#include "VertexData.h"

class Triangle : public Geometry{
	public:
	VertexData v0;
	VertexData v1;
	VertexData v2;
	glm::vec3 normal;
	glm::vec3 tangent;
	glm::vec3 bitangent;
	glm::mat3 TBN;
	bool smooth;

	Triangle(VertexData v0, VertexData v1, VertexData v2, bool smooth);

	//ObjectIntersection intersect(const Ray& ray, const Material& material) override;
	ObjectIntersection intersect(const Ray& ray) override;

	glm::vec3 randomPoint() override;
};


#endif //CG_PATH_TRACER_TRIANGLE_H
