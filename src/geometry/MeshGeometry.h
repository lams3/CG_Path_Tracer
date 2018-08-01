//
// Created by luca on 25/06/18.
//

#ifndef CG_PATH_TRACER_MESHGEOMETRY_H
#define CG_PATH_TRACER_MESHGEOMETRY_H


#include <vector>
#include "../../dependencies/glm/glm.hpp"
#include "Geometry.h"
#include "Triangle.h"

class MeshGeometry : public Geometry {

	std::vector<Triangle> triangles;
    Geometry* boundingGeometry;

	private:
	void computeBoundingGeometry();

	public:
	explicit MeshGeometry(std::vector<Triangle>& triangles);

    ObjectIntersection intersect(const Ray& ray) override;

	glm::vec3 randomPoint() override;
};


#endif //CG_PATH_TRACER_MESHGEOMETRY_H
