//
// Created by Raed Alsheikh Amin on 3/07/2025.
//

#ifndef INC_477HW1_SCENEPARSER_H
#define INC_477HW1_SCENEPARSER_H
#include <fstream>
#include <vector>
#include "Vector3.h"
#include "Scene.h"
#include "Camera.h"
#include "Material.h"
#include "Light.h"
#include "Sphere.h"
#include "Triangle.h"
#include "RayTracer.h"
#include "Mesh.h"

class SceneParser {
public:
    static bool parseScene(const std::string& filename, Scene& scene, Camera& camera, RayTracer& rayTracer);
};


#endif //INC_477HW1_SCENEPARSER_H
