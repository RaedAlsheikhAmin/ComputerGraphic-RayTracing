//
// Created by Raed Alsheikh Amin on 3/12/2025.
//



#ifndef INC_477HW1_SCENE_H
#define INC_477HW1_SCENE_H

#include <vector>
#include "Object.h"
#include "Light.h"
#include "Vector3.h"

// This class holds all the data needed to describe the scene: objects, lights, materials, etc.
class Scene {
public:
    std::vector<Object*> objects;       // All geometric objects in the scene
    std::vector<Light> lights;          // All light sources (including ambient)
    std::vector<Material> materials;    // List of materials to assign to objects
    Vector3 backgroundColor;            // Background color (used when a ray hits nothing)

    Scene(const Vector3& backgroundColor); // Constructor

    void addObject(Object* obj);           // Add a geometry to the scene
    void addLight(const Light& light);     // Add a light source to the scene

    // Finds the closest object that intersects with the given ray
    bool getClosestIntersection(const Ray& ray, float& t, Object*& closestObject) const;
};

#endif
