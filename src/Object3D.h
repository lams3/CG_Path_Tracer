//
// Created by luca on 24/06/18.
//

#ifndef CG_PATH_TRACER_OBJECT3D_H
#define CG_PATH_TRACER_OBJECT3D_H


#include <string>
#include "Geometry.h"
#include "Material.h"
#include "Ray.h"
#include "ObjectIntersection.h"

class Object3D {
public:
    Geometry* geometry;
    Material* material;

    Object3D(Geometry* geometry, Material* material);

    std::string toString();

    ObjectIntersection intersect(const Ray& ray);
};


#endif //CG_PATH_TRACER_OBJECT3D_H
