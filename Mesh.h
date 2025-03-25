//
// Created by Hi on 3/25/2025.
//

#ifndef INC_477HW1_MESH_H
#define INC_477HW1_MESH_H

#include <vector>
#include "Triangle.h"
#include "Object.h"

class Mesh : public Object {
public:
    std::vector<Triangle*> triangles;

    Mesh(const std::vector<Triangle*>& triangles, const Material& material);
    ~Mesh();

    bool intersect(const Ray& ray, float& t) const override;
    Vector3 getNormal(const Vector3& hitPoint) const override;
};


#endif //INC_477HW1_MESH_H
