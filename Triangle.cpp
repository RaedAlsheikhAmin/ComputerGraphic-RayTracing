//
// Created by Raed Alsheikh Amin on 3/10/2025.
//


#include "Triangle.h"

// Constructor: just stores the three vertices and the material
Triangle::Triangle(Vector3 v0, Vector3 v1, Vector3 v2, Material material)
        : Object(material), v0(v0), v1(v1), v2(v2) {}

// This is where the intersection test happens
// I use the Möller–Trumbore algorithm.
bool Triangle::intersect(const Ray& ray, float& t) const {
    Vector3 edge1 = v1 - v0;   // first edge of triangle
    Vector3 edge2 = v2 - v0;   // second edge

    // Compute determinant (dot product of edge1 and cross of ray dir and edge2)
    Vector3 h = ray.direction.cross(edge2);
    float a = edge1.dot(h);

    // If determinant is too close to zero, the ray is parallel to the triangle
    if (fabs(a) < 1e-6) return false;

    float f = 1.0f / a;
    Vector3 s = ray.origin - v0;
    float u = f * s.dot(h);

    // If u is outside the triangle, we miss
    if (u < 0.0 || u > 1.0)
        return false;

    Vector3 q = s.cross(edge1);
    float v = f * ray.direction.dot(q);

    // If v is outside or u + v is too big, we're outside the triangle
    if (v < 0.0 || u + v > 1.0)
        return false;

    // At this point, the ray hits the triangle at distance t
    float tempT = f * edge2.dot(q);
    if (tempT > 1e-4) {  // we want t to be positive (in front of the camera)
        t = tempT;
        return true;
    }

    return false;  // hit is too close or behind camera
}

// Normal is calculated using the cross product of two triangle edges
// The order matters (right-hand rule) and we normalize it
Vector3 Triangle::getNormal(const Vector3& hitPoint) const {
    Vector3 edge1 = v1 - v0;
    Vector3 edge2 = v2 - v0;
    Vector3 normal = edge1.cross(edge2).normalize();


    return normal;
}

