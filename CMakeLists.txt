cmake_minimum_required(VERSION 3.25)
project(477hw1)

set(CMAKE_CXX_STANDARD 11)

add_executable(RayTracer main.cpp Scene.h Scene.cpp RayTracer.cpp RayTracer.h Vector3.h Ray.cpp Ray.h Camera.cpp Camera.h Material.cpp Material.h Object.cpp Object.h Sphere.cpp Sphere.h Triangle.cpp Triangle.h PPMWriter.cpp PPMWriter.h Light.cpp Light.h SceneParser.cpp SceneParser.h Mesh.cpp Mesh.h)
