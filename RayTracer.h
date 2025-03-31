//
// Created by Raed Alsheikh Amin on 3/14/2025.
//



#ifndef INC_477HW1_RAYTRACER_H
#define INC_477HW1_RAYTRACER_H

#include "Scene.h"
#include "Camera.h"

class RayTracer {
public:
    int maxDepth; // for recurssion and to return background colour
    float shadowRayEpsilon;

    RayTracer(int maxDepth, float shadowRayEpsilon);

    Vector3 traceRay(const Ray& ray, const Scene& scene, int depth);
};

#endif
