//
// Created by luca on 24/06/18.
//

#include <fstream>
#include "SceneLoader.h"
#include "CameraLoader.h"
#include "ObjectLoader.h"

void SceneLoader::load(const std::string& path, Scene*& scene) {
    std::ifstream sceneFile(path);
    std::string input;

    std::string subPath = path.substr(0, path.find_last_of('/') + 1);

    ObjectLoader objectLoader;
    CameraLoader cameraLoader;

    scene = new Scene;
    while (sceneFile.good()) {
        sceneFile >> input;
        if (input == "camera") {
            sceneFile >> input;
            Camera* camera;
            cameraLoader.load(subPath + input, camera);
            scene->add(camera);
        } else if (input == "object") {
            sceneFile >> input;
            Object3D* object;
            objectLoader.load(subPath + input, object);
            scene->add(object);
        } else if (input == "light") {
            sceneFile >> input;
            Light* light;
            Object3D* object;
            objectLoader.load(subPath + input, object);
            float r, g, b, intensity;
            sceneFile >> r >> g >> b >> intensity;
            light = new Light(object->geometry, glm::vec3(r, g, b), intensity);
            scene->add(light);
        }
    }

    sceneFile.close();
}
