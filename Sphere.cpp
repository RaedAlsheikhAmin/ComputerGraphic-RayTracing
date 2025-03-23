#include "Sphere.h"

Sphere::Sphere(Vector3 center, float radius, Material material)
        : Object(material), center(center), radius(radius) {}

bool Sphere::intersect(const Ray& ray, float& t) {
    Vector3 oc = ray.origin - center;
    float b = 2.0 * oc.dot(ray.direction);
    float c = oc.dot(oc) - radius * radius;
    float discriminant = b * b - 4 * c;

    if (discriminant < 0) return false;
    t = (-b - sqrt(discriminant)) / 2.0;
    return true;
}
