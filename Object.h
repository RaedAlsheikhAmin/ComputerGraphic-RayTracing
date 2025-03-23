#ifndef OBJECT_H
#define OBJECT_H

#include "Vector3.h"
#include "Ray.h"
#include "Material.h"

class Object {
public:
    Material material;

    Object(Material material);
    virtual bool intersect(const Ray& ray, float& t) = 0;
};

#endif
