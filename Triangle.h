#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Object.h"

class Triangle : public Object {
public:
    Vector3 v0, v1, v2, normal;

    Triangle(Vector3 v0, Vector3 v1, Vector3 v2, Material material);
    bool intersect(const Ray& ray, float& t) override;
};

#endif
