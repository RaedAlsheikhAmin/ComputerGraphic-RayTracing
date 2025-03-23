#ifndef SPHERE_H
#define SPHERE_H

#include "Object.h"
#include "Vector3.h"

class Sphere : public Object {
public:
    Vector3 center;
    float radius;

    Sphere(Vector3 center, float radius, Material material);
    bool intersect(const Ray& ray, float& t) override;
};

#endif
