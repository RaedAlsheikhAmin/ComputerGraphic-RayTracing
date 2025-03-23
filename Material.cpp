#include "Material.h"

Material::Material(const Vector3& ambient, const Vector3& diffuse, const Vector3& specular, float phongExponent, const Vector3& mirror)
        : ambient(ambient), diffuse(diffuse), specular(specular), phongExponent(phongExponent), mirror(mirror) {}
