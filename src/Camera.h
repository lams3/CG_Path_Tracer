//
// Created by luca on 24/06/18.
//

#ifndef CG_PATH_TRACER_CAMERA_H
#define CG_PATH_TRACER_CAMERA_H


#include <glm/glm.hpp>
#include <string>
#include "Ray.h"

class Camera {
private:
    glm::vec3 position;
    glm::vec3 xAxis, yAxis, zAxis;
    glm::ivec2 resolution;
    float fov;
    float f;


public:
    Camera(glm::vec3 position, glm::vec3 target, glm::vec3 up,
           glm::ivec2 resolution, float fov, float f);

    std::string toString();

    glm::ivec2 getResolution();

    Ray getRay(glm::vec2 coords);
};


#endif //CG_PATH_TRACER_CAMERA_H
