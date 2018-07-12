//
// Created by luca on 29/06/18.
//

#include "ObjectIntersection.h"

ObjectIntersection::ObjectIntersection(float t, glm::vec3 position, glm::vec3 normal, Material *material) {
    this->t = t;
    this->position = position;
    this->normal = normal;
    this->material = material;
}
