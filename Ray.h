//
// Created by Raed Alsheikh Amin on 3/10/2025.
//




#ifndef INC_477HW1_RAY_H
#define INC_477HW1_RAY_H

#include "Vector3.h"
// A basic Ray class with an origin point and a direction vector.
class Ray {
public:
    Vector3 origin, direction;

    Ray(const Vector3& origin, const Vector3& direction);
};

#endif
