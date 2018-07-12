//
// Created by luca on 24/06/18.
//

#ifndef CG_PATH_TRACER_SCENE_H
#define CG_PATH_TRACER_SCENE_H


#include <vector>
#include "Camera.h"
#include "Object3D.h"
#include "Light.h"
#include "Ray.h"

class Scene {

private:
    std::vector<Camera*> cameras;
    std::vector<Object3D*> objects;
    std::vector<Object3D *> lights;

public:
    Scene();

    void add(Camera* camera);
    void add(Object3D* object);
    void addLight(Object3D* light);
    std::vector<Camera *> getCameras();
    std::vector<Object3D *> getObjects();
    std::vector<Object3D *> getLights();
    glm::vec3 trace(const Ray& ray, int depth);
    ObjectIntersection intersect(const Ray& ray);
};


#endif //CG_PATH_TRACER_SCENE_H
