//
// Created by Raed Alsheikh Amin on 3/10/2025.
//



#include "Ray.h"

// This constructor initializes a ray starting from 'origin' and pointing in a certain 'direction'.
// We make sure to normalize the direction vector immediately so we don’t carry unnecessary length around.
// Normalizing helps with clean math when computing intersections and lighting.
Ray::Ray(const Vector3& origin, const Vector3& direction)
        : origin(origin), direction(direction.normalize()) {}
