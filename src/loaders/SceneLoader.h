//
// Created by luca on 24/06/18.
//

#ifndef CG_PATH_TRACER_SCENELOADER_H
#define CG_PATH_TRACER_SCENELOADER_H

#include <string>
#include "../core/Scene.h"

class SceneLoader {

public:
    void load(const std::string& path, Scene*& scene);
};


#endif //CG_PATH_TRACER_SCENELOADER_H
