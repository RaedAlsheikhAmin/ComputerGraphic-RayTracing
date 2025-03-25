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
        float tTemp;
        if (tri->intersect(ray, tTemp) && tTemp < closestT) {
            closestT = tTemp;
            hit = true;
        }
    }

    if (hit) {
        t = closestT;
    }
    return hit;
}

Vector3 Mesh::getNormal(const Vector3& hitPoint) const {
    if (!triangles.empty()) {
        return triangles[0]->getNormal(hitPoint);  // Use first triangle's normal
    }
    return Vector3(0, 0, 0);
}
