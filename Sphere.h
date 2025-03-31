//
// Created by Raed Alsheikh Amin on 3/09/2025.
//



#ifndef INC_477HW1_SPHERE_H
#define INC_477HW1_SPHERE_H

#include "Object.h"
#include "Vector3.h"

class Sphere : public Object {
public:
    Vector3 center;
    float radius;

    Sphere(Vector3 center, float radius, Material material);
    bool intersect(const Ray& ray, float& t) const override;
    Vector3 getNormal(const Vector3 &hitPoint) const override;
};

#endif
