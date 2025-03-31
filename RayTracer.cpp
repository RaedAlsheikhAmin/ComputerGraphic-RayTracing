#include "RayTracer.h"
#include <cmath>
#include <algorithm>
#include <iostream>

RayTracer::RayTracer(int maxDepth, float shadowRayEpsilon)
        : maxDepth(maxDepth), shadowRayEpsilon(shadowRayEpsilon) {}

Vector3 RayTracer::traceRay(const Ray& ray, const Scene& scene, int depth) {
    if (depth > maxDepth) {
        std::cout << "[traceRay] Max recursion depth reached.\n";
        return scene.backgroundColor;
    }

    float t;
    Object* hitObject = nullptr;

    if (!scene.getClosestIntersection(ray, t, hitObject)) {
        std::cout << "[traceRay] No hit. Returning background color.\n";
        return scene.backgroundColor;
    }

    Vector3 hitPoint = ray.origin + ray.direction * t;
    Vector3 normal = hitObject->getNormal(hitPoint).normalize();
    Vector3 viewDir = -ray.direction.normalize();

    std::cout << "\n[traceRay] Hit object at depth " << depth << "\n";
    std::cout << "  Hit Point: (" << hitPoint.x << ", " << hitPoint.y << ", " << hitPoint.z << ")\n";
    std::cout << "  Normal:    (" << normal.x << ", " << normal.y << ", " << normal.z << ")\n";

    Vector3 color(0, 0, 0);

    // Ambient Light
    for (const auto& light : scene.lights) {
        if (light.position == Vector3(0, 0, 0)) {
            Vector3 ambient = hitObject->material.ambient * light.intensity;
            color += ambient;
            std::cout << "  Ambient: (" << ambient.x << ", " << ambient.y << ", " << ambient.z << ")\n";
        }
    }

    for (const auto& light : scene.lights) {
        if (light.position == Vector3(0, 0, 0)) continue;

        Vector3 lightDir = (light.position - hitPoint).normalize();
        float distance = (light.position - hitPoint).length();
        distance = std::max(distance, shadowRayEpsilon);

        Ray shadowRay(hitPoint + normal * shadowRayEpsilon, lightDir);
        Object* shadowObj = nullptr;
        float shadowT;
        bool inShadow = scene.getClosestIntersection(shadowRay, shadowT, shadowObj) && shadowT < distance;

        if (inShadow) {
            std::cout << "  In shadow. Skipping light at (" << light.position.x << ", " << light.position.y << ", " << light.position.z << ")\n";
            continue;
        }

        // Diffuse
        float diffFactor = std::max(normal.dot(lightDir), 0.0f);
        Vector3 diffuse = hitObject->material.diffuse * light.intensity * diffFactor;
        std::cout << "  Diffuse: factor=" << diffFactor << "  color=(" << diffuse.x << ", " << diffuse.y << ", " << diffuse.z << ")\n";

        // Specular
        Vector3 halfVec = (viewDir + lightDir).normalize();
        float specFactor = std::pow(std::max(normal.dot(halfVec), 0.0f), hitObject->material.phongExponent);
        Vector3 specular = hitObject->material.specular * light.intensity * specFactor;
        std::cout << "  Specular: factor=" << specFactor << "  color=(" << specular.x << ", " << specular.y << ", " << specular.z << ")\n";

        color += diffuse + specular;
    }

    // Mirror reflection
    if (hitObject->material.mirror.x > 0 || hitObject->material.mirror.y > 0 || hitObject->material.mirror.z > 0) {
        Vector3 reflectDir = (ray.direction - normal * 2.0f * normal.dot(ray.direction)).normalize();
        Ray reflectRay(hitPoint + normal * shadowRayEpsilon, reflectDir);
        Vector3 reflection = traceRay(reflectRay, scene, depth + 1);
        color += hitObject->material.mirror * reflection;
        std::cout << "  Reflection color: (" << reflection.x << ", " << reflection.y << ", " << reflection.z << ")\n";
    }

    // Clamp
    color.x = std::min(std::max(color.x, 0.0f), 1.0f);
    color.y = std::min(std::max(color.y, 0.0f), 1.0f);
    color.z = std::min(std::max(color.z, 0.0f), 1.0f);

    // Gamma correction
    color.x = std::pow(color.x, 1.0f / 2.2f);
    color.y = std::pow(color.y, 1.0f / 2.2f);
    color.z = std::pow(color.z, 1.0f / 2.2f);

    std::cout << "  Final Color (Gamma Corrected): (" << color.x << ", " << color.y << ", " << color.z << ")\n";

    return color;
}
