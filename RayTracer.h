#ifndef RAYTRACER_H
#define RAYTRACER_H

#include "Scene.h"
#include "Camera.h"

class RayTracer {
public:
    int maxDepth;
    float shadowRayEpsilon;

    RayTracer(int maxDepth, float shadowRayEpsilon);

    Vector3 traceRay(const Ray& ray, const Scene& scene, int depth);
};

#endif
