
#include <iostream>
#include "Renderer.h"
#include "Scene.h"
#include "SceneLoader.h"

int main(int argc, char* argv[]) {
    if (argc < 2)
        exit(1);

    Scene* scene;
    SceneLoader loader;
    loader.load(argv[1], scene);

    Renderer renderer;
    renderer.render(scene, atoi(argv[2]));

    return 0;
}