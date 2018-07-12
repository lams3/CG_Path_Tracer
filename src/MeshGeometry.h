//
// Created by luca on 25/06/18.
//

#ifndef CG_PATH_TRACER_MESHGEOMETRY_H
#define CG_PATH_TRACER_MESHGEOMETRY_H


#include <glm/vec3.hpp>
#include <vector>
#include "Geometry.h"

class MeshGeometry : public Geometry {
    std::vector<glm::vec3> vertices;
    std::vector<glm::ivec3> faces;
	std::vector<glm::vec3> normals;

public:
    MeshGeometry(std::vector<glm::vec3>& vertices, std::vector<glm::ivec3>& faces, std::vector<glm::vec3>& normals);

    std::string toString();

    ObjectIntersection intersect(const Ray& ray) override ;

	void barycentric(glm::vec3 vec, glm::vec3 v0, glm::vec3 v1, glm::vec3 v2, float &u, float &d, float &w);
};


#endif //CG_PATH_TRACER_MESHGEOMETRY_H
