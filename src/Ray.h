//
// Created by luca on 25/06/18.
//

#ifndef CG_PATH_TRACER_RAY_H
#define CG_PATH_TRACER_RAY_H

#include <glm/glm.hpp>

class Ray {
public:
    glm::vec3 origin, direction;
    float minDistance;

    Ray(glm::vec3 origin, glm::vec3 direction, float minDistance);
};


#endif //CG_PATH_TRACER_RAY_H
