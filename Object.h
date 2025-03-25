#ifndef INC_477HW1_OBJECT_H
#define INC_477HW1_OBJECT_H

#include "Vector3.h"
#include "Ray.h"
#include "Material.h"

class Object {
public:
    Material material;

    Object(Material material);
    virtual bool intersect(const Ray& ray, float& t) const = 0;
    virtual Vector3 getNormal(const Vector3& hitPoint) const = 0;
};

#endif
