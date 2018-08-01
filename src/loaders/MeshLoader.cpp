//
// Created by luca on 25/06/18.
//
#include <glm/glm.hpp>
#include "MeshLoader.h"
#include "../geometry/MeshGeometry.h"
#include "../core/Material.h"
#include "../geometry/Triangle.h"
#define TINYOBJLOADER_IMPLEMENTATION
#include "../../dependencies/tiny_obj_loader.h"


void MeshLoader::load(const std::string &path, MeshGeometry*& mesh, glm::vec3 position, float scale, Material* material) {
	tinyobj::attrib_t attrib;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;
    std::string err;

	if (!tinyobj::LoadObj(&attrib, &shapes, &materials, &err, path.c_str()))
        exit(-1);

    std::vector<glm::vec3> vertices;
    std::vector<glm::vec3> normals;
	std::vector<glm::vec3> backupNormals;
    std::vector<glm::vec2> textCoords;
    std::vector<glm::ivec3> faces;
    std::vector<Triangle> triangles;

    vertices = this->toVec3(attrib.vertices);
    normals = this->toVec3(attrib.normals);
    textCoords = this->toVec2(attrib.texcoords);

    for (auto& vertex: vertices)
    	vertex = position + vertex * scale;

    for (auto& vertex : vertices)
    	backupNormals.push_back(glm::vec3(0.0, 0.0, 0.0));

    for (const auto& shape : shapes) {
    	const auto& indices = shape.mesh.indices;
    	for (int i = 0; i < indices.size(); i += 3) {
    		faces.push_back(
    				glm::ivec3(
    						indices[i].vertex_index,
						    indices[i + 1].vertex_index,
						    indices[i + 2].vertex_index
				    )
		    );
    	}
    }

    for (const auto& face : faces) {
    	glm::vec3 v0 = vertices[face.x];
    	glm::vec3 v1 = vertices[face.y];
    	glm::vec3 v2 = vertices[face.z];
    	glm::vec3 normal = glm::normalize(glm::cross(v1 - v0, v2 - v0));
	    backupNormals[face.x] += normal;
	    backupNormals[face.y] += normal;
	    backupNormals[face.z] += normal;
    }

    for (auto& normal : backupNormals)
    	normal = glm::normalize(normal);

	for (auto& normal : normals)
		normal = glm::normalize(normal);

    for (const auto& shape : shapes) {
        const auto& indices = shape.mesh.indices;
        for (int i = 0; i < indices.size(); i += 3) {
	        int iv0 = indices[i].vertex_index;
	        int in0 = indices[i].normal_index;
	        int it0 = indices[i].texcoord_index;

	        int iv1 = indices[i + 1].vertex_index;
	        int in1 = indices[i + 1].normal_index;
	        int it1 = indices[i + 1].texcoord_index;

	        int iv2 = indices[i + 2].vertex_index;
	        int in2 = indices[i + 2].normal_index;
	        int it2 = indices[i + 2].texcoord_index;


        	VertexData v0(
        			vertices[iv0],
			        in0 == -1 ? backupNormals[iv0] : normals[in0],
			        it0 == -1 ? glm::vec2(0.0, 0.0) : textCoords[it0]
	        );

	        VertexData v1(
			        vertices[iv1],
			        in1 == -1 ? backupNormals[iv1] : normals[in1],
			        it1 == -1 ? glm::vec2(0.0, 0.0) : textCoords[it1]
	        );

	        VertexData v2(
			        vertices[iv2],
			        in2 == -1 ? backupNormals[iv2] : normals[in2],
			        it2 == -1 ? glm::vec2(0.0, 0.0) : textCoords[it2]
	        );

	        if (material && material->displacementMap.active) {
	        	Texture displacement = material->displacementMap;
	        	float factor = displacement.max / 255.0f;

	        	glm::vec2 v0ImgCoords = glm::vec2(displacement.w, displacement.h) * v0.textCoords;
	        	v0ImgCoords = glm::vec2(floorf(v0ImgCoords.x), floorf(v0ImgCoords.y));
	        	float v0d = factor * displacement.data[int(v0ImgCoords.y * displacement.h + v0ImgCoords.x)];
	        	v0.position += v0d * v0.normal;

		        glm::vec2 v1ImgCoords = glm::vec2(displacement.w, displacement.h) * v1.textCoords;
		        v1ImgCoords = glm::vec2(floorf(v1ImgCoords.x), floorf(v1ImgCoords.y));
		        float v1d = factor * displacement.data[int(v1ImgCoords.y * displacement.h + v1ImgCoords.x)];
		        v1.position += v1d * v1.normal;

		        glm::vec2 v2ImgCoords = glm::vec2(displacement.w, displacement.h) * v2.textCoords;
		        v2ImgCoords = glm::vec2(floorf(v2ImgCoords.x), floorf(v2ImgCoords.y));
		        float v2d = factor * displacement.data[int(v2ImgCoords.y * displacement.h + v2ImgCoords.x)];
		        v2.position += v2d * v2.normal;
	        }

	        triangles.push_back(Triangle(v0, v1, v2, material->smooth));
        }
    }

    mesh = new MeshGeometry(triangles);
}

std::vector<glm::vec2> MeshLoader::toVec2(std::vector<float> vector) {
	std::vector<glm::vec2> result;
	for (int i = 0; i < vector.size(); i += 2) {
		result.push_back(
				glm::vec2(
						vector[i],
						vector[i + 1]
				)
		);
	}
	return result;
}

std::vector<glm::vec3> MeshLoader::toVec3(std::vector<float> vector) {
	std::vector<glm::vec3> result;
	for (int i = 0; i < vector.size(); i += 3) {
		result.push_back(
				glm::vec3(
						vector[i],
						vector[i + 1],
						vector[i + 2]
				)
		);
	}
	return result;
}
