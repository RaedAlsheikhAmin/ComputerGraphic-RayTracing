//
// Created by Raed Alsheikh Amin on 3/14/2025.
//



#include "RayTracer.h"
#include <cmath>
#include <algorithm>
#include <iostream>


// Constructor initializes the recursion depth limit and shadow epsilon
RayTracer::RayTracer(int maxDepth, float shadowRayEpsilon)
        : maxDepth(maxDepth), shadowRayEpsilon(shadowRayEpsilon) {}



/*
 * Step 1: Base Case – Max Depth
If we've hit the maximum recursion depth, just return the background color.


Step 2: Ray-Object Intersection
Cast the ray into the scene, find the nearest object it intersects.


Step 3: Compute Hit Information
Calculate the exact point of intersection, surface normal, and the view direction (from point back to camera).
  - Normalize all directions to ensure accurate lighting

Step 4: Ambient Lighting (Global Light)
If there’s an ambient light in the scene (fake one using position (0,0,0)), multiply it with the material’s ambient color and add to result.
   Ambient = ka * Ia

Step 5: Loop Over Point Lights
For each real (non-ambient) light:
  a. Compute direction to light (L) and distance
  b. Cast a shadow ray from the surface point toward the light
    Use shadow ray to detect occlusion
  c. If in shadow => skip this light

  If not in shadow:
    - Diffuse= kd * Ii * max(0, N·L)

    - Specular = ks * Ii * max(0, N·H)^p
       (Blinn-Phong model)
    - Add both to the final color

Step 6: Mirror Reflection (Recursive) :) I just wanted to try this one for fun
If the material has a mirror component:
  a. Reflect the ray around the normal to get the reflection direction
  b. Launch a new ray in that direction, increase depth
  c. Multiply the reflected color with the mirror coefficient and add


Step 7: Gamma Correction // I deleted this step, but I will keep it as a note for myself, it was making the image too bright which affected the shadow
Brighten the final color to match how humans perceive light
  - Done via: color = pow(color, 1/2.2)
  - Helps if images look darker than expected

Step 8: Clamp Final Color// I learnt this from the internet, It made the image look better
Clip the RGB values to the [0, 1] range to avoid overflow
Ready to convert to [0–255] during image writing

 */
Vector3 RayTracer::traceRay(const Ray& ray, const Scene& scene, int depth) {
    // If we've bounced too many times, return background color
    if (depth > maxDepth) return scene.backgroundColor;

    float t;
    Object* hitObject = nullptr;

    // Find the closest object the ray hits
    if (!scene.getClosestIntersection(ray, t, hitObject))
        return scene.backgroundColor;

    // Compute intersection point and surface normal
    Vector3 hitPoint = ray.origin + ray.direction * t;
    Vector3 normal = hitObject->getNormal(hitPoint).normalize();
    Vector3 viewDir = -ray.direction.normalize(); // From hit point to eye

    // Start accumulating color from black
    Vector3 color(0, 0, 0);

    // We check for a light at (0,0,0) to represent ambient light
    for (const auto& light : scene.lights) {
        if (light.position == Vector3(0, 0, 0)) {
            color += hitObject->material.ambient * light.intensity;
        }
    }

    //  DIFFUSE + SPECULAR LIGHTING
    for (const auto& light : scene.lights) {
        if (light.position == Vector3(0, 0, 0)) continue; // Skip ambient

        Vector3 lightDir = (light.position - hitPoint).normalize();
        float distance = (light.position - hitPoint).length();
        distance = std::max(distance, shadowRayEpsilon); // Prevent divide-by-zero

        Ray shadowRay(hitPoint + normal * shadowRayEpsilon, lightDir);
        Object* shadowObj = nullptr;
        float shadowT;

        bool inShadow = scene.getClosestIntersection(shadowRay, shadowT, shadowObj) && shadowT < distance;

        if (!inShadow) {
            float attenuation = 1.0f / (distance * distance);

            // Diffuse
            float diff = std::max(normal.dot(lightDir), 0.0f);
            Vector3 diffuse = hitObject->material.diffuse * light.intensity * diff * attenuation;

            // Specular
            Vector3 halfVec = (viewDir + lightDir).normalize();
            float spec = std::pow(std::max(normal.dot(halfVec), 0.0f), hitObject->material.phongExponent);
            Vector3 specular = hitObject->material.specular * light.intensity * spec * attenuation;

            color += diffuse + specular;
        }
    }

    //  REFLECTION / MIRROR COLOR  < I added this extra just for fun, for later on I may use my code for rendering some images.
    if (hitObject->material.mirror.x > 0 || hitObject->material.mirror.y > 0 || hitObject->material.mirror.z > 0) {
        // Reflect the ray around the normal
        Vector3 reflectDir = (ray.direction - normal * 2.0f * normal.dot(ray.direction)).normalize();
        Ray reflectRay(hitPoint + normal * shadowRayEpsilon, reflectDir);

        // Recursively trace the reflected ray
        Vector3 reflection = traceRay(reflectRay, scene, depth + 1);
        color += hitObject->material.mirror * reflection;
    }


    // Clamp values to [0, 1] range just in case anything overflowed
    color.x = std::min(std::max(color.x, 0.0f), 1.0f);
    color.y = std::min(std::max(color.y, 0.0f), 1.0f);
    color.z = std::min(std::max(color.z, 0.0f), 1.0f);





    return color;
}
