//
// Created by luca on 24/06/18.
//

#include <fstream>
#include "SceneLoader.h"
#include "CameraLoader.h"
#include "ObjectLoader.h"
#include "SphereGeometry.h"

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
	        glm::vec3 color;
	        float kd, ks, kt;
	        sceneFile >> input >> color.r >> color.g >> color.b >> kd >> ks >> kt;
            Object3D* object;
            objectLoader.load(subPath + input, object);
            object->material = Material::makeObjectMaterial(kd, ks, kt, color);
            scene->add(object);
        } else if (input == "sphere") {
            glm::vec3 position;
            float r;
            sceneFile >> position.x >> position.y >> position.z >> r;
            glm::vec3 color;
	        float kd, ks, kt;
	        sceneFile >> color.r >> color.g >> color.b >> kd >> ks >> kt;
	        Object3D* object = new Object3D(
			        new SphereGeometry(position, r),
			        Material::makeObjectMaterial(kd, ks, kt, color)
	        );
			scene->add(object);
        } else if (input == "light") {
            glm::vec3 color;
            float intensity;
            sceneFile >> input >> color.r >> color.g >> color.b >> intensity;
            Object3D* object;
            objectLoader.load(subPath + input, object);
            object->material = Material::makeLightMaterial(intensity, color);
            scene->addLight(object);
        }
    }

    sceneFile.close();
}
