//
// Created by Raed Alsheikh Amin on 3/10/2025.
//



#ifndef INC_477HW1_OBJECT_H
#define INC_477HW1_OBJECT_H

#include "Vector3.h"
#include "Ray.h"
#include "Material.h"

// Base class for all objects in the scene (Sphere, Triangle, Mesh)

class Object {
public:
    Material material;  // Every object has a material (ambient, diffuse, specular, mirror)

    Object(Material material);

    // Pure virtual functions: every derived object must implement these, so they will override what the object has.
    virtual bool intersect(const Ray& ray, float& t) const = 0;
    virtual Vector3 getNormal(const Vector3& hitPoint) const = 0;        // Needed for shading
};

#endif
