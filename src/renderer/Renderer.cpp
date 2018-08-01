//
// Created by luca on 24/06/18.
//

#include <cmath>
#include <iostream>
#include "../../dependencies/SDL2/SDL.h"
#include "Renderer.h"

Renderer::Renderer() = default;

void Renderer::drawBuffer(SDL_Renderer* renderer, std::vector<glm::vec3>& buffer, glm::ivec2 resolution, int samples) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
	float g = 1.0f / 2.2f;
	for (int i = 0; i < resolution.x; i++) {
	    for (int j = 0; j < resolution.y; j++) {
            glm::vec3 color = buffer[j * resolution.x + i] / (float) samples;
            color = glm::clamp(color, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
            color = glm::vec3(powf(color.x, g), powf(color.y, g), powf(color.z, g));
            SDL_SetRenderDrawColor(renderer, Uint8(std::lround(255 * color.r)), Uint8(std::lround(255 * color.g)), Uint8(std::lround(255 * color.b)), 255);
            SDL_RenderDrawPoint(renderer, i, j);
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

    for (int s = 1; s <= nSamples; s++) {
	    drawBuffer(renderer, buffer, camera->getResolution(), s);
	    int j;
	    time_t start, stop;
	    start = SDL_GetTicks();
	    #pragma omp parallel for schedule(dynamic, 1) private(j)
	    for (int i = 0; i < camera->getResolution().x; i++) {
		    for (j = 0; j < camera->getResolution().y; j++) {
			    int index = j * camera->getResolution().x + i;
			    buffer[index] +=
					    scene->trace(camera->getRay(glm::vec2(i, j)), 0, glm::vec3(1.0f, 1.0f, 1.0f));
		    }
		    SDL_PollEvent(nullptr);
		    std::cout << i << std::endl;
        }
        stop = SDL_GetTicks();
	    std::cout << stop - start << std::endl;
	    std::cout << "progress: " << (100.0f * ((float)s / nSamples)) << "%" << "(" << s << "/" << nSamples << ")" << std::endl;
	}

	std::cout << "Finished!" << std::endl;

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
