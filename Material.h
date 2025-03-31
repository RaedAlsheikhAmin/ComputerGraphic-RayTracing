//
// Created by Raed Alsheikh Amin on 3/10/2025.
//


#ifndef INC_477HW1_MATERIAL_H
#define INC_477HW1_MATERIAL_H

#include "Vector3.h"

// Material class holds the shading parameters for objects.
// These parameters are used in ray tracing for light interaction calculations.
class Material {
public:
    Vector3 ambient;   // Ambient reflection component
    Vector3 diffuse;   // Diffuse reflection component
    Vector3 specular;  // Specular reflection component
    Vector3 mirror;    // Mirror reflection component
    float phongExponent; // Controls specular sharpness (Blinn-Phong model)

    Material(const Vector3& ambient, const Vector3& diffuse,
             const Vector3& specular, float phongExponent,
             const Vector3& mirror);
};

#endif
