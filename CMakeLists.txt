cmake_minimum_required(VERSION 3.10)
project(CG_Path_Tracer)

set(CMAKE_CXX_STANDARD 17)

add_executable(CG_Path_Tracer src/main.cpp src/Renderer.cpp src/Renderer.h src/Scene.cpp src/Scene.h src/SceneLoader.cpp src/SceneLoader.h src/Camera.cpp src/Camera.h src/Object3D.cpp src/Object3D.h src/Light.cpp src/Light.h src/CameraLoader.cpp src/CameraLoader.h src/ObjectLoader.cpp src/ObjectLoader.h src/MeshGeometry.cpp src/MeshGeometry.h src/Material.cpp src/Material.h src/Geometry.cpp src/Geometry.h src/Ray.cpp src/Ray.h src/ObjectIntersection.cpp src/ObjectIntersection.h)

target_link_libraries(CG_Path_Tracer SDL2)