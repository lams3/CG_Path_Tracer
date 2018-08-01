//
// Created by luca on 24/06/18.
//

#include <fstream>
#include "SceneLoader.h"
#include "CameraLoader.h"
#include "MeshLoader.h"
#include "MaterialLoader.h"
#include "../geometry/SphereGeometry.h"
#include "../geometry/MeshGeometry.h"

void SceneLoader::load(const std::string& path, Scene*& scene) {
    std::ifstream sceneFile(path);
    std::string input;

    std::string subPath = path.substr(0, path.find_last_of('/') + 1);

    MeshLoader meshLoader;
    CameraLoader cameraLoader;
    MaterialLoader materialLoader;

    scene = new Scene;
    while (sceneFile.good()) {
        sceneFile >> input;
        if (input == "camera") {
            sceneFile >> input;
            Camera* camera;
            cameraLoader.load(subPath + input, camera);
	        scene->addCamera(camera);
        } else if (input == "mesh") {
            std::string meshPath, mtlPath;
            sceneFile >> meshPath >> mtlPath;
            Object3D* object;
	        MeshGeometry* mesh;
            Material* material;
            materialLoader.load(subPath + mtlPath, material);
            meshLoader.load(subPath + meshPath, mesh, glm::vec3(0.0, 0.0, 0.0), 1.0, material);
            object = new Object3D(mesh, material);
            scene->addObject(object);
        } else if (input == "sphere") {
            glm::vec3 position;
            float r;
            std::string mtlPath;
            sceneFile >> position.x >> position.y >> position.z >> r >> mtlPath;
            Object3D* object;
            MeshGeometry* mesh;
            Material* material;
            materialLoader.load(subPath + mtlPath, material);
            meshLoader.load("./resources/sphere.obj", mesh, position, r, material);
            object = new Object3D(mesh, material);
            scene->addObject(object);
        } else if (input == "light") {
            glm::vec3 color;
            float intensity;
            sceneFile >> input >> color.r >> color.g >> color.b >> intensity;
            Object3D* object;
            MeshGeometry* mesh;
            Material* material;
            material = Material::makeLightMaterial(intensity, color);
            meshLoader.load(subPath + input, mesh, glm::vec3(0.0, 0.0, 0.0), 1.0, material);
            object = new Object3D(mesh, material);
            scene->addLight(object);
        }
    }

    sceneFile.close();
}
