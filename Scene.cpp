//
// Created by Raed Alsheikh Amin on 3/12/2025.
//



#include "Scene.h"
#include "Vector3.h"
#include <vector>

// Constructor Implementation
// This just sets the background color for the scene – basically what you'll see
// if the ray doesn't hit anything (like the skybox or empty space).
Scene::Scene(const Vector3& backgroundColor) : backgroundColor(backgroundColor) {}

// This function adds an object (like a sphere, triangle, or mesh) to the scene.
// The ray tracer will later loop through this list when checking for intersections.
void Scene::addObject(Object* obj) {
    objects.push_back(obj);
}

// Similar to addObject(), this adds a light source to the scene.
// These lights are used during shading to calculate how bright and colorful a point should be.
void Scene::addLight(const Light& light) {
    lights.push_back(light);
}

// This function does the heavy job during ray tracing.
// It finds the closest object that the given ray hits in the scene.
// If it hits something, it updates the 't' value (which is how far the hit point is from the ray origin)
// and sets 'closestObject' to point to the object it hit.
bool Scene::getClosestIntersection(const Ray& ray, float& t, Object*& closestObject) const {
    t = INFINITY; // Start with the assumption that nothing is hit
    closestObject = nullptr;
    bool hit = false;

    // Loop through every object in the scene and test for intersection
    for (const auto& obj : objects) {
        float tempT;
        // If this object is hit and it's the closest so far, update our result
        if (obj->intersect(ray, tempT) && tempT < t) {
            t = tempT;
            closestObject = obj;
            hit = true;
        }
    }

    // Return whether any object was hit at all
    return hit;
}
