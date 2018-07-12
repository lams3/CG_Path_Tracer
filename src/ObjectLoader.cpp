//
// Created by luca on 25/06/18.
//
#define TINYOBJLOADER_IMPLEMENTATION
#include "ObjectLoader.h"
#include "MeshGeometry.h"
#include "Material.h"
#include <tiny_obj_loader.h>
#include <glm/glm.hpp>
#include <iostream>


void ObjectLoader::load(const std::string &path, Object3D*& object) {
    tinyobj::attrib_t attrib;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;
    std::string err;

    if (!tinyobj::LoadObj(&attrib, &shapes, &materials, &err, path.c_str()))
        exit(-1);



    std::vector<glm::vec3> vertices;
    std::vector<glm::vec3> normals;
    std::vector<glm::ivec3> faces;

    for (int i = 0; i < attrib.vertices.size(); i += 3) {
        vertices.push_back(
                glm::vec3(
                        attrib.vertices[i],
                        attrib.vertices[i + 1],
                        attrib.vertices[i + 2]
                )
        );
        normals.push_back(glm::vec3());
    }

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
	    normals[face.x] += normal;
	    normals[face.y] += normal;
	    normals[face.z] += normal;
    }

    for (auto& normal : normals)
    	normal = glm::normalize(normal);


	std::cout << path << std::endl;
	std::cout << "vertices" << std::endl;
	for (auto v : vertices)
		std::cout << v.x << " " << v.y << " " << v.z << std::endl;
	std::cout << "normals" << std::endl;
	for (auto v : normals)
		std::cout << v.x << " " << v.y << " " << v.z << std::endl;
	std::cout << "faces" << std::endl;
	for (auto v : faces)
		std::cout << v.x << " " << v.y << " " << v.z << std::endl;

    object = new Object3D (
        new MeshGeometry(vertices, faces, normals),
        nullptr
    );
}
