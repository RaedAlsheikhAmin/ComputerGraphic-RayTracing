#ifndef INC_477HW1_LIGHT_H
#define INC_477HW1_LIGHT_H

#include "Vector3.h"

class Light {
public:
    Vector3 position;
    Vector3 intensity;

    Light(const Vector3& position, const Vector3& intensity);
};

#endif
