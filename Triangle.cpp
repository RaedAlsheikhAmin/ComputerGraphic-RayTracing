#include "Triangle.h"

Triangle::Triangle(Vector3 v0, Vector3 v1, Vector3 v2, Material material)
        : Object(material), v0(v0), v1(v1), v2(v2) {
    normal = (v1 - v0).cross(v2 - v0).normalize();
}

bool Triangle::intersect(const Ray& ray, float& t) const {
    Vector3 edge1 = v1 - v0, edge2 = v2 - v0;
    Vector3 h = ray.direction.cross(edge2);
    float a = edge1.dot(h);

    if (fabs(a) < 1e-6) return false; // Ray parallel to triangle

    float f = 1.0 / a;
    Vector3 s = ray.origin - v0;
    float u = f * s.dot(h);

    if (u < 0.0 || u > 1.0) return false;

    Vector3 q = s.cross(edge1);
    float v = f * ray.direction.dot(q);

    if (v < 0.0 || u + v > 1.0) return false;

    t = f * edge2.dot(q);
    return (t > 1e-6);
}
Vector3 Triangle::getNormal(const Vector3& hitPoint) const {
    return (v1 - v0).cross(v2 - v0).normalize();
}