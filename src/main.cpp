
#include <iostream>
#include "Renderer.h"
#include "Scene.h"
#include "SceneLoader.h"

int main(int argc, char* argv[]) {
	time_t start, stop;
	time(&start);

	if (argc < 2)
        exit(1);

    int samples = argc < 3 ? INT_MAX : atoi(argv[2]);

    Scene* scene;
    SceneLoader loader;
    loader.load(argv[1], scene);

    Renderer renderer;
    renderer.render(scene, samples);


	time(&stop);
	double diff = difftime(stop, start);
	int hrs = (int)diff/3600;
	int mins = ((int)diff/60)-(hrs*60);
	int secs = (int)diff-(hrs*3600)-(mins*60);
	printf("\rRendering (%i samples): Complete!\nTime Taken: %i hrs, %i mins, %i secs\n\n", samples, hrs, mins, secs);

	return 0;
}