//
// Created by luca on 24/06/18.
//

#include <iostream>
#include <SDL2/SDL.h>
#include "Renderer.h"

Renderer::Renderer() = default;

void Renderer::drawBuffer(SDL_Renderer* renderer, std::vector<glm::vec3>& buffer, glm::ivec2 resolution, int samples) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    for (int i = 0; i < resolution.x; i++) {
        for (int j = 0; j < resolution.y; j++) {
            glm::vec3 color = buffer[j * resolution.x + i] / (float) samples;
            SDL_SetRenderDrawColor(renderer, (int) (255 * color.r), (int) (255 * color.g), (int) (255 * color.b), 255);
            SDL_RenderDrawPoint(renderer, j, i);
        }
    }
    SDL_RenderPresent(renderer);
}

void Renderer::render(Scene*& scene, int nSamples) {
    Camera* camera = scene->getCameras()[0];

    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_CreateWindowAndRenderer(camera->getResolution().x, camera->getResolution().y, 0, &window, &renderer);

    std::vector<glm::vec3> buffer(camera->getResolution().x * camera->getResolution().y);
    for (auto& v : buffer)
        v = glm::vec3(0.0, 0.0, 0.0);

    for (int s = 0; s < nSamples; s++) {
        drawBuffer(renderer, buffer, camera->getResolution(), s);
        std::cout << "progress: " << (100.0f * ((float)s / nSamples)) << "%" << std::endl;
        for (int i = 0; i < camera->getResolution().y; i++) {
            for (int j = 0; j < camera->getResolution().x; j++) {
                buffer[j * camera->getResolution().x + i] +=
                        scene->trace(camera->getRay(glm::vec2(j, i)), 0);
            }
            SDL_PollEvent(nullptr);
        }
    }

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
