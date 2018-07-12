//
// Created by luca on 24/06/18.
//

#ifndef CG_PATH_TRACER_RENDERER_H
#define CG_PATH_TRACER_RENDERER_H


#include "Scene.h"

class Renderer {
public:
    Renderer();

    void render(Scene*& scene, int nSamples);
};


#endif //CG_PATH_TRACER_RENDERER_H
