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
	Geometry* boundingGeometry;

	private:

	void barycentric(glm::vec3 vec, glm::vec3 v0, glm::vec3 v1, glm::vec3 v2, float &u, float &d, float &w);

	void computeBoundingGeometry();

	public:
    MeshGeometry(std::vector<glm::vec3>& vertices, std::vector<glm::ivec3>& faces, std::vector<glm::vec3>& normals);

    MeshGeometry(const float radius, const glm::vec3& center, int segments = 3);

    std::string toString();

    ObjectIntersection intersect(const Ray& ray) override ;

	glm::vec3 randomPoint() override;
};


#endif //CG_PATH_TRACER_MESHGEOMETRY_H
