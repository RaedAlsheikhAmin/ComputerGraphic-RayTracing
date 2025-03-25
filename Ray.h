#ifndef INC_477HW1_RAY_H
#define INC_477HW1_RAY_H

#include "Vector3.h"

class Ray {
public:
    Vector3 origin, direction;

    Ray(const Vector3& origin, const Vector3& direction);
};

#endif
