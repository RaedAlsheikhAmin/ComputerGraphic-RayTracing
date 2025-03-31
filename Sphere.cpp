#include "Sphere.h"
//Ray: R(t) = o + t*d
//Sphere center: c, radius: r
//||R(t) - c||^2 = r^2
//→ At^2 + Bt + C = 0
Sphere::Sphere(Vector3 center, float radius, Material material)
        : Object(material), center(center), radius(radius) {}

bool Sphere::intersect(const Ray& ray, float& t) const {
    Vector3 oc = ray.origin - center;
    float a = ray.direction.dot(ray.direction);
    float b = 2.0f * oc.dot(ray.direction);
    float c = oc.dot(oc) - radius * radius;

    float discriminant = b * b - 4 * a * c;

    if (discriminant < 0) return false;

    float sqrtD = std::sqrt(discriminant);
    float t1 = (-b - sqrtD) / (2 * a);
    float t2 = (-b + sqrtD) / (2 * a);

    if (t1 > 1e-4) t = t1;
    else if (t2 > 1e-4) t = t2;
    else return false;

    return true;
}

Vector3 Sphere::getNormal(const Vector3& hitPoint) const {
    return (hitPoint - center).normalize();
}
