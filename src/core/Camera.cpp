//
// Created by luca on 24/06/18.
//

#include "Camera.h"

Camera::Camera(glm::vec3 position, glm::vec3 target, glm::vec3 up, glm::ivec2 resolution, float fov, float f) {
    this->position = position;
    this->zAxis = glm::normalize(position - target);
    this->xAxis = glm::normalize(glm::cross(up, this->zAxis));
    this->yAxis = glm::normalize(glm::cross(this->zAxis, this->xAxis));
    this->resolution = resolution;
    this->fov = glm::radians(fov);
    this->f = f;
}

glm::ivec2 Camera::getResolution() {
    return this->resolution;
}

Ray Camera::getRay(glm::vec2 coords) {
    glm::vec2 h;
    h.x = this->f * tanf(this->fov / 2);
    h.y = h.x * (float(this->resolution.y) / float(this->resolution.x));

    glm::vec3 point;

    point.x = h.x * (2.0f * ((coords.x / (float)this->resolution.x) - 0.5f));
    point.y = -h.y * (2.0f * ((coords.y / (float)this->resolution.y) - 0.5f));
    point.z = -this->f;

    float r1 = ((float) rand() / RAND_MAX) - 0.5f;
    float r2 = ((float) rand() / RAND_MAX) - 0.5f;
    glm::vec2 pixelSize = h / glm::vec2(this->resolution.x, this->resolution.y);

    point.x += r1 * pixelSize.x;
    point.y += r2 * pixelSize.y;

    glm::mat4 toCanonic = glm::mat4(
            glm::vec4(this->xAxis, 0.0f),
            glm::vec4(this->yAxis, 0.0f),
            glm::vec4(this->zAxis, 0.0f),
            glm::vec4(this->position, 1.0f)
    );

    point = glm::vec3(toCanonic * glm::vec4(point, 1.0f));

    return Ray(this->position, point - this->position, this->f);
}
