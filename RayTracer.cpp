#include "RayTracer.h"

RayTracer::RayTracer(int maxDepth, float shadowRayEpsilon)
        : maxDepth(maxDepth), shadowRayEpsilon(shadowRayEpsilon) {}

Vector3 RayTracer::traceRay(const Ray& ray, const Scene& scene, int depth) {
    if (depth > maxDepth) return scene.backgroundColor;
    

    float t;
    Object* hitObject = nullptr;

    if (!scene.getClosestIntersection(ray, t, hitObject))
        return scene.backgroundColor;

    Vector3 hitPoint = ray.origin + ray.direction * t;
    Vector3 normal = hitObject->getNormal(hitPoint);
    Vector3 viewDir = -ray.direction;

    Vector3 color = hitObject->material.ambient;

    for (const auto& light : scene.lights) {
        Vector3 lightDir = (light.position - hitPoint).normalize();
        float distance = (light.position - hitPoint).length();
        Vector3 attenuatedIntensity = light.intensity / (distance * distance); // ✅ Light Attenuation

        // Shadow Ray Setup
        Ray shadowRay(hitPoint + normal * shadowRayEpsilon, lightDir);
        Object* shadowObject = nullptr;
        float shadowT;

        if (!scene.getClosestIntersection(shadowRay, shadowT, shadowObject)) {
            // Diffuse Component
            float diff = std::max(normal.dot(lightDir), 0.0f);
            color += hitObject->material.diffuse * attenuatedIntensity * diff;

            // ✅ Blinn-Phong Specular Component
            Vector3 halfVector = (viewDir + lightDir).normalize();
            float spec = pow(std::max(normal.dot(halfVector), 0.0f), hitObject->material.phongExponent);
            color += hitObject->material.specular * attenuatedIntensity * spec;
        }
    }

    // Reflection Handling
    if (hitObject->material.mirror.x > 0) {
        Vector3 reflectDir = (ray.direction - normal * 2.0f * normal.dot(ray.direction)).normalize();
        Ray reflectRay(hitPoint + normal * shadowRayEpsilon, reflectDir);
        color += hitObject->material.mirror * traceRay(reflectRay, scene, depth + 1);
    }

    return color;
}
