//
// Created by luca on 24/06/18.
//

#ifndef CG_PATH_TRACER_RENDERER_H
#define CG_PATH_TRACER_RENDERER_H

#include "../../dependencies/SDL2/SDL.h"
#include "../core/Scene.h"

class Renderer {
public:
    Renderer();

    void render(Scene*& scene, int nSamples);

	void drawBuffer(SDL_Renderer *renderer, std::vector<glm::vec3> &buffer, glm::ivec2 resolution, int samples);
};


#endif //CG_PATH_TRACER_RENDERER_H
