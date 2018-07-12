//
// Created by luca on 25/06/18.
//

#ifndef CG_PATH_TRACER_GEOMETRY_H
#define CG_PATH_TRACER_GEOMETRY_H


#include <string>
#include "Ray.h"
#include "ObjectIntersection.h"

class Geometry {
public:
    virtual std::string toString() = 0;

    virtual ObjectIntersection intersect(const Ray& ray) = 0;
};


#endif //CG_PATH_TRACER_GEOMETRY_H
