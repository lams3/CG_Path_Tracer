//
// Created by luca on 29/06/18.
//

#ifndef CG_PATH_TRACER_OBJECTINTERSECTION_H
#define CG_PATH_TRACER_OBJECTINTERSECTION_H


#include <glm/glm.hpp>
#include "Material.h"

class ObjectIntersection {
public:
    float t;
    glm::vec3 position;
    glm::vec3 normal;
    Material* material;

    ObjectIntersection(float t, glm::vec3 position, glm::vec3 normal, Material* material);
};


#endif //CG_PATH_TRACER_OBJECTINTERSECTION_H
