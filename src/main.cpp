#include "core/Scene.h"
#include "loaders/SceneLoader.h"
#include "renderer/Renderer.h"

int main(int argc, char* argv[]) {
	if (argc < 2)
        exit(1);

    int samples = argc < 3 ? INT_MAX : atoi(argv[2]);

    Scene* scene;
    SceneLoader loader;
    loader.load(argv[1], scene);

    Renderer renderer;
    renderer.render(scene, samples);

	return 0;
}