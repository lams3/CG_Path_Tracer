//
// Created by luca on 29/06/18.
//

#include "ObjectIntersection.h"

//const ObjectIntersection ObjectIntersection::EMPTY = ObjectIntersection(-1, glm::vec3(), glm::vec3(), glm::vec3(), nullptr);
const ObjectIntersection ObjectIntersection::EMPTY(-1, VertexData(), glm::mat3(), nullptr);

ObjectIntersection::ObjectIntersection(float t, VertexData v, glm::mat3 TBN, Material *m) {
	this->t = t;
	this->v = v;
	this->TBN = TBN;
	this->material = m;
}

glm::vec3 ObjectIntersection::shadeNormal() {
	if (this->material) {
		Texture t = this->material->normalMap;
		if (t.active) {
			glm::vec2 imgCoords = glm::vec2(t.w, t.h) * this->v.textCoords;
			imgCoords = glm::vec2(floorf(imgCoords.x), floorf(imgCoords.y));
			float factor = 1.0f / 255.0f;
			glm::vec3 mapNormal = factor * glm::vec3(
					t.data[3 * int(imgCoords.y * t.h + imgCoords.x)],
					t.data[3 * int(imgCoords.y * t.h + imgCoords.x) + 1],
					t.data[3 * int(imgCoords.y * t.h + imgCoords.x) + 2]
			);
			mapNormal = glm::normalize(mapNormal * 2.0f - 1.0f);
			return glm::normalize(this->TBN * mapNormal);
		}
	}
	return this->v.normal;
}

glm::vec3 ObjectIntersection::shadeColor() {
	if (this->material) {
		Texture t = this->material->diffuseMap;
		if (t.active) {
			glm::vec2 imgCoords = glm::vec2(t.w, t.h) * this->v.textCoords;
			imgCoords = glm::vec2(floorf(imgCoords.x), floorf(imgCoords.y));
			float factor = 1.0f / 255.0f;
			glm::vec3 color = factor * glm::vec3(
					t.data[3 * int(imgCoords.y * t.h + imgCoords.x)],
					t.data[3 * int(imgCoords.y * t.h + imgCoords.x) + 1],
					t.data[3 * int(imgCoords.y * t.h + imgCoords.x) + 2]
			);
			return color;
		}
		return this->material->color;
	};
	return glm::vec3(0.0, 0.0, 0.0);
}

glm::vec3 ObjectIntersection::shadePosition() {
	return this->v.position;
}

/*ObjectIntersection::ObjectIntersection(float t, glm::vec3 position, glm::vec3 normal, glm::vec3 color, Material *material) {
    this->t = t;
    this->position = position;
    this->normal = normal;
    this->material = material;
    this->color = color;
}*/
