//
// Created by luca on 24/06/18.
//

#include <iostream>
#include <SDL2/SDL.h>
#include "Renderer.h"

Renderer::Renderer() = default;

void Renderer::render(Scene*& scene, int nSamples) {
    Camera* camera = scene->getCameras()[0];

    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_CreateWindowAndRenderer(camera->getResolution().x, camera->getResolution().y, 0, &window, &renderer);

    SDL_Delay(100);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    for (int i = 0; i < camera->getResolution().y; i++) {
        std::cout << "progress: " << (100.0f * ((float)i / camera->getResolution().y)) << "%" << std::endl;
        for (int j = 0; j < camera->getResolution().x; j++) {
            glm::vec3 color = glm::vec3();
            for (int s = 0; s < nSamples; s++) {
                color += scene->trace(camera->getRay(glm::vec2(j, i)), 0) / (float) nSamples;
            }
            SDL_SetRenderDrawColor(renderer, (int) 255 * color.r, (int) 255 * color.g, (int) 255 * color.b, 255);
            SDL_RenderDrawPoint(renderer, j, i);
        }
        SDL_RenderPresent(renderer);
        SDL_PollEvent(nullptr);
    }

    std::cout << glm::length(glm::vec3(1.0, 1.0, 1.0)) << std::endl;

    while (true) {
        SDL_Event e;
        SDL_PollEvent(&e);
        if (e.type == SDL_QUIT)
            break;
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
