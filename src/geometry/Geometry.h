//
// Created by luca on 25/06/18.
//

#ifndef CG_PATH_TRACER_GEOMETRY_H
#define CG_PATH_TRACER_GEOMETRY_H


#include <string>
#include "../core/Ray.h"
#include "../core/ObjectIntersection.h"

class Geometry {
public:
    virtual ObjectIntersection intersect(const Ray& ray) = 0;

	virtual glm::vec3 randomPoint() = 0;
};


#endif //CG_PATH_TRACER_GEOMETRY_H
