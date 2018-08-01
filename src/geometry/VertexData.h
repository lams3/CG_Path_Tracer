//
// Created by luca on 30/07/18.
//

#ifndef CG_PATH_TRACER_VERTEXDATA_H
#define CG_PATH_TRACER_VERTEXDATA_H


#include "../../dependencies/glm/glm.hpp"

class VertexData {
	public:
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 textCoords;

	VertexData(glm::vec3 position, glm::vec3 normal, glm::vec2 textCoords);

	VertexData();
};


#endif //CG_PATH_TRACER_VERTEXDATA_H
