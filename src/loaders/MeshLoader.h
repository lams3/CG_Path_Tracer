//
// Created by luca on 25/06/18.
//

#ifndef CG_PATH_TRACER_OBJECTLOADER_H
#define CG_PATH_TRACER_OBJECTLOADER_H


#include <string>
#include <vector>
#include "../geometry/MeshGeometry.h"

class MeshLoader {
public:
    void load(const std::string& path, MeshGeometry*& mesh, glm::vec3 position, float scale, Material* material);

	std::vector<glm::vec3> toVec3(std::vector<float> vector);

	std::vector<glm::vec2> toVec2(std::vector<float> vector);
};


#endif //CG_PATH_TRACER_OBJECTLOADER_H
