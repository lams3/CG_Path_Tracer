//
// Created by luca on 25/06/18.
//

#include "Ray.h"

Ray::Ray(glm::vec3 origin, glm::vec3 direction, float minDistance) {
    this->origin = origin;
    this->direction = glm::normalize(direction);
    this->minDistance = minDistance;
}

glm::vec3 Ray::sample(float t)const {
    return this->origin + t * this->direction;
}

glm::vec3 Ray::getOrigin() const {
    return this->origin;
}

void Ray::setOrigin(const glm::vec3 &origin) {
    this->origin = origin;
}

const glm::vec3 &Ray::getDirection() const {
    return this->direction;
}

void Ray::setDirection(const glm::vec3 &direction) {
    this->direction = glm::normalize(direction);
}



