#include "Mesh.h"

Mesh::Mesh(const std::vector<Triangle*>& triangles, const Material& material)
        : Object(material), triangles(triangles) {}

Mesh::~Mesh() {
    for (Triangle* tri : triangles) {
        delete tri;
    }
}

bool Mesh::intersect(const Ray& ray, float& t) const {
    bool hit = false;
    float closestT = INFINITY;

    for (const auto& tri : triangles) {
        float tempT;
        if (tri->intersect(ray, tempT) && tempT < closestT) {
            closestT = tempT;
            hit = true;
        }
    }

    if (hit) t = closestT;
    return hit;
}

Vector3 Mesh::getNormal(const Vector3& hitPoint) const {
    // Optional: could compute per-triangle normal, but we'll return first
    if (!triangles.empty()) {
        return triangles[0]->getNormal(hitPoint);
    }
    return Vector3(0, 0, 0);
}
