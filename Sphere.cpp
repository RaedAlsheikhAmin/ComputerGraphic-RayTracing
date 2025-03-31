//
// Created by Raed Alsheikh Amin on 3/09/2025.
//


#include "Sphere.h"

// This is just recalling the math behind sphere-ray intersection.
// A ray is defined as: R(t) = o + t*d, where o is origin and d is direction.
// A sphere is defined by (P - c)·(P - c) = r^2 where c is center and r is radius.
// Substituting the ray into the sphere equation gives us a quadratic in terms of t.
// This is what we solve to check if the ray hits the sphere.

Sphere::Sphere(Vector3 center, float radius, Material material)
        : Object(material), center(center), radius(radius) {}

// This function checks if the ray intersects the sphere.
// If it does, it returns true and sets t to the closest intersection distance.
bool Sphere::intersect(const Ray& ray, float& t) const {
    Vector3 oc = ray.origin - center;  // vector from ray origin to sphere center
    float a = ray.direction.dot(ray.direction);  // should be 1 if direction is normalized
    float b = 2.0f * oc.dot(ray.direction);
    float c = oc.dot(oc) - radius * radius;

    float discriminant = b * b - 4 * a * c;  // classic quadratic formula

    // If the discriminant is negative, the ray doesn't hit the sphere
    if (discriminant < 0)
        return false;

    float sqrtD = std::sqrt(discriminant);
    float t1 = (-b - sqrtD) / (2 * a);  // closer hit
    float t2 = (-b + sqrtD) / (2 * a);  // farther hit

    // We want the smallest t that is still in front of the camera (greater than epsilon)
    if (t1 > 1e-4) t = t1;
    else if (t2 > 1e-4) t = t2;
    else
        return false;

    return true;  // ray hits the sphere
}

// This just returns the normal at the hit point on the sphere surface.
// It's the vector from the center to the hit point, normalized.
Vector3 Sphere::getNormal(const Vector3& hitPoint) const {
    return (hitPoint - center).normalize();
}
