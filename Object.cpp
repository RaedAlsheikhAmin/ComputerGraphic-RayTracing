//
// Created by Raed Alsheikh Amin on 3/10/2025.
//


#include "Object.h"

// This is the base class constructor.
// Every object (like spheres, triangles, meshes) has a material.
// We just store the given material here, so later when we shade the object,
// we know how it should look (color, shininess, reflectivity, etc.).
Object::Object(Material material) : material(material) {}
