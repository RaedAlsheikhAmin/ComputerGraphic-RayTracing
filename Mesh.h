//
// Created by Raed Alsheikh Amin on 3/10/2025.
//

#ifndef INC_477HW1_MESH_H
#define INC_477HW1_MESH_H

#include <vector>
#include "Triangle.h"
#include "Object.h"

// Represents a mesh made up of triangles (usually read from a file)
// Inherits from Object so it can be added to the scene
class Mesh : public Object {
public:
    Mesh(const std::vector<Triangle*>& triangles, const Material& material);
    ~Mesh();

    bool intersect(const Ray& ray, float& t) const override;
    Vector3 getNormal(const Vector3& hitPoint) const override;

private:
    std::vector<Triangle*> triangles; // vector that containes triangles that define a mesh
    mutable const Triangle* lastHitTriangle; // For retrieving correct normal
};

#endif //INC_477HW1_MESH_H
