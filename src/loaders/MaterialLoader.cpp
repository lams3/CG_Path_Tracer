//
// Created by luca on 28/07/18.
//

#include <fstream>
#include "MaterialLoader.h"
#define STB_IMAGE_IMPLEMENTATION
#include "../../dependencies/stb_image.h"

void MaterialLoader::load(const std::string &path, Material *&material) {
	std::ifstream mtlFile(path);
	std::string input;

	std::string subPath = path.substr(0, path.find_last_of('/') + 1);

	material = new Material;
	material->displacementMap.active = false;
	material->displacementMap.data = nullptr;
	material->normalMap.active = false;
	material->normalMap.data = nullptr;
	material->diffuseMap.active = false;
	material->diffuseMap.data = nullptr;
	material->light = false;
	while (mtlFile.good()) {
		mtlFile >> input;
		if (input == "color")
			mtlFile >> material->color.r >> material->color.g >> material->color.b;
		else if (input == "ka")
			mtlFile >> material->ka;
		else if (input == "kd")
			mtlFile >> material->kd;
		else if (input == "ks")
			mtlFile >> material->ks;
		else if (input == "kt")
			mtlFile >> material->kt;
		else if (input == "kr")
			mtlFile >> material->kr;
		else if (input == "n")
			mtlFile >> material->n;
		else if (input == "smooth") {
			mtlFile >> input;
			material->smooth = input == "true";
		} else if (input == "displacementMap") {
			mtlFile >> input >> material->displacementMap.max;
			material->displacementMap.data = stbi_load(
					(subPath + input).c_str(),
					&material->displacementMap.w,
					&material->displacementMap.h,
					&material->displacementMap.n,
					1
			);
			if (material->displacementMap.data)
				material->displacementMap.active = true;
		} else if (input == "normalMap") {
			mtlFile >> input;
			material->normalMap.data = stbi_load(
					(subPath + input).c_str(),
					&material->normalMap.w,
					&material->normalMap.h,
					&material->normalMap.n,
					3
			);
			if (material->normalMap.data)
				material->normalMap.active = true;
		} else if (input == "diffuseMap") {
			mtlFile >> input;
			material->diffuseMap.data = stbi_load(
					(subPath + input).c_str(),
					&material->diffuseMap.w,
					&material->diffuseMap.h,
					&material->diffuseMap.n,
					3
			);
			if (material->diffuseMap.data)
				material->diffuseMap.active = true;
		}
	}
}
