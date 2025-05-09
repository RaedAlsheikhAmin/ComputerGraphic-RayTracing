//
// Created by Raed Alsheikh Amin on 3/10/2025.
//

#ifndef INC_477HW1_TRIANGLE_H
#define INC_477HW1_TRIANGLE_H

#include "Object.h"
//this class is explained will in the cpp file
class Triangle : public Object {
public:
    Vector3 v0, v1, v2, normal;

    Triangle(Vector3 v0, Vector3 v1, Vector3 v2, Material material);
    bool intersect(const Ray& ray, float& t) const override;
    Vector3 getNormal(const Vector3 &hitPoint) const override;
};

#endif
