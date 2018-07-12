//
// Created by luca on 25/06/18.
//

#include "CameraLoader.h"
#include <glm/glm.hpp>
#include <fstream>

void CameraLoader::load(const std::string &path, Camera*& camera) {
    std::ifstream cameraFile(path);
    std::string input;

    glm::vec3 position = glm::vec3();
    glm::vec3 target = glm::vec3(0, 0, -1);
    glm::vec3 up = glm::vec3(0, 1, 0);
    glm::ivec2 resolution = glm::vec2(800, 600);
    float fov = 45;
    float f = 0.1;

    while (cameraFile.good()) {
        cameraFile >> input;
        if (input == "position")
            cameraFile >> position.x >> position.y >> position.z;
        else if (input == "target")
            cameraFile >> target.x >> target.y >> target.z;
        else if (input == "up")
            cameraFile >> up.x >> up.y >> up.z;
        else if (input == "fov")
            cameraFile >> fov;
        else if (input == "resolution")
            cameraFile >> resolution.x >> resolution.y;
        else if (input == "f")
            cameraFile >> f;
    }

    camera = new Camera(position, target, up, resolution, fov, f);
}
