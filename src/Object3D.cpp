//
// Created by luca on 24/06/18.
//

#include <sstream>
#include "Object3D.h"
#include "ObjectIntersection.h"

Object3D::Object3D(Geometry *geometry, Material *material) {
    this->geometry = geometry;
    this->material = material;
}

std::string Object3D::toString() {
    std::ostringstream ss;
    ss << "Geometry: " << std::endl << (this->geometry->toString()) << std::endl;
    ss << "Material: " << std::endl << (this->material->toString()) << std::endl;
    return ss.str();
}

ObjectIntersection Object3D::intersect(const Ray &ray) {
    ObjectIntersection intersection = this->geometry->intersect(ray);
    intersection.material = this->material;
    return intersection;
}

glm::vec3 Object3D::randomPoint() {
    return this->geometry->randomPoint();
}