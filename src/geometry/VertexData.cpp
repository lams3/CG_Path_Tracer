//
// Created by luca on 30/07/18.
//

#include "VertexData.h"

VertexData::VertexData() {
	this->position = glm::vec3(0.0, 0.0, 0.0);
	this->normal = glm::vec3(0.0, 0.0, 0.0);
	this->textCoords = glm::vec2(0.0, 0.0);
}

VertexData::VertexData(glm::vec3 position, glm::vec3 normal, glm::vec2 textCoords) {
	this->position = position;
	this->normal = normal;
	this->textCoords = textCoords;
}
