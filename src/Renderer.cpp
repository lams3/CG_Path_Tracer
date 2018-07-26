//
// Created by luca on 24/06/18.
//

#include <iostream>
#include <SDL2/SDL.h>
#include "Renderer.h"

Renderer::Renderer() = default;

void Renderer::drawBuffer(SDL_Renderer* renderer, std::vector<glm::vec3>& buffer, glm::ivec2 resolution, int samples, int index) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
	float g = 1.0f / 2.2f;
	for (int i = 0; i < resolution.x; i++) {
	    for (int j = 0; j < resolution.y; j++) {
            glm::vec3 color = (buffer[j * resolution.x + i] / (float) ((i <= index) ? samples : (samples - 1)));
            color = glm::clamp(color, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
            color = glm::vec3(powf(color.x, g), powf(color.y, g), powf(color.z, g));
            if (i == index)
            	color = glm::vec3(0.0f, 0.0f, 1.0f);
	        SDL_SetRenderDrawColor(renderer, (int) ((255 * color.r) + 0.5), (int) ((255 * color.g) + 0.5), (int) ((255 * color.b) + 0.5), 255);
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
	    drawBuffer(renderer, buffer, camera->getResolution(), s, 0);
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
		    //std::cout << i << std::endl;
	            //std::cout << i << std::endl;
	        SDL_PollEvent(nullptr);
	        //if (i % 10 == 0)
		    //    drawBuffer(renderer, buffer, camera->getResolution(), s, i);
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
