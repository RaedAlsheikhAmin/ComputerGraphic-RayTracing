#ifndef MATERIAL_H
#define MATERIAL_H

#include "Vector3.h"

class Material {
public:
    Vector3 ambient, diffuse, specular, mirror;
    float phongExponent;

    Material(const Vector3& ambient, const Vector3& diffuse, const Vector3& specular, float phongExponent, const Vector3& mirror);
};

#endif
