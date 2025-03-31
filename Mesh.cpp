//
// Created by Raed Alsheikh Amin on 3/10/2025.
//

#include "Mesh.h"

// Constructor: store triangles and material
Mesh::Mesh(const std::vector<Triangle*>& triangles, const Material& material)
        : Object(material), triangles(triangles), lastHitTriangle(nullptr) {}

// Destructor: clean up dynamically allocated triangle objects
Mesh::~Mesh() {
    for (Triangle* tri : triangles) {
        delete tri;
    }
}

// Intersect ray with all triangles, keep closest hit and remember which triangle was hit
bool Mesh::intersect(const Ray& ray, float& t) const {
    bool hit = false;
    float closestT = INFINITY;// just to make sure the first one is far away
    lastHitTriangle = nullptr;

    for (const auto& tri : triangles) {
        float tempT;
        if (tri->intersect(ray, tempT) && tempT < closestT) {
            closestT = tempT;
            hit = true;
            lastHitTriangle = tri;
        }
    }

    if (hit) {
        t = closestT;
    }

    return hit;
}

// Return normal from the triangle that was hit
Vector3 Mesh::getNormal(const Vector3& hitPoint) const {
    if (lastHitTriangle != nullptr) {
        return lastHitTriangle->getNormal(hitPoint);
    }
    return Vector3(0, 0, 0); // fallback if nothing hit
}
