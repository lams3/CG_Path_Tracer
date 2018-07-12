//
// Created by luca on 25/06/18.
//

#include "Ray.h"

Ray::Ray(glm::vec3 origin, glm::vec3 direction, float minDistance) {
    this->origin = origin;
    this->direction = glm::normalize(direction);
    this->minDistance = minDistance;
}
