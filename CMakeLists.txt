cmake_minimum_required(VERSION 3.10)
project(CG_Path_Tracer)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenMP)
if (OPENMP_FOUND)
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif()

file(COPY resources DESTINATION ${CMAKE_BINARY_DIR})

add_executable(CG_Path_Tracer src/main.cpp src/renderer/Renderer.cpp src/renderer/Renderer.h src/core/Scene.cpp src/core/Scene.h src/loaders/SceneLoader.cpp src/loaders/SceneLoader.h src/core/Camera.cpp src/core/Camera.h src/core/Object3D.cpp src/core/Object3D.h src/loaders/CameraLoader.cpp src/loaders/CameraLoader.h src/loaders/MeshLoader.cpp src/loaders/MeshLoader.h src/geometry/MeshGeometry.cpp src/geometry/MeshGeometry.h src/core/Material.cpp src/core/Material.h src/geometry/Geometry.cpp src/geometry/Geometry.h src/core/Ray.cpp src/core/Ray.h src/core/ObjectIntersection.cpp src/core/ObjectIntersection.h src/geometry/SphereGeometry.cpp src/geometry/SphereGeometry.h src/geometry/Triangle.cpp src/geometry/Triangle.h src/loaders/MaterialLoader.cpp src/loaders/MaterialLoader.h src/geometry/BoxGeometry.cpp src/geometry/BoxGeometry.h src/geometry/VertexData.cpp src/geometry/VertexData.h)

target_link_libraries(CG_Path_Tracer SDL2)