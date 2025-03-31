//
// Created by Raed Alsheikh Amin on 3/10/2025.
//

#include "Material.h"
// This constructor sets all the lighting properties of a surface material.
// These are the key components used in shading from the slides:
// - Ambient: how the object appears under general ambient light
// - Diffuse: how the object reflects light in a matte way (depends on angle of light)
// - Specular: shiny highlights (based on Blinn-Phong)
// - Phong exponent: controls how shiny the specular highlight is (higher = tighter spot)
// - Mirror : controls reflectivity for recursive reflection rays
Material::Material(const Vector3& ambient, const Vector3& diffuse, const Vector3& specular, float phongExponent, const Vector3& mirror)
        : ambient(ambient), diffuse(diffuse), specular(specular), phongExponent(phongExponent), mirror(mirror) {}
