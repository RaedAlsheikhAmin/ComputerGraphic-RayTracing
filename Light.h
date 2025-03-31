//
// Created by Raed Alsheikh Amin on 3/09/2025.
// Reference: https://raytracing.github.io/books/RayTracingInOneWeekend.html#outputanimage/theppmimageformat

#ifndef INC_477HW1_LIGHT_H
#define INC_477HW1_LIGHT_H

#include "Vector3.h"

/**
 * Light class represents either an ambient or point light source in the scene.
 *
 * - For ambient light, we fake it by giving it a position of (0, 0, 0),
 *   which helps us easily identify it in the ray tracer loop and skip shadow checks.
 *
 * - For point lights, the position is their actual (x, y, z)
 *   location in 3D space, and the intensity is how strong the light is in RGB.
 *
 * The light intensities are normalized during scene parsing so we can just
 * multiply them directly with material color components later.
 */
class Light {
public:
    Vector3 position;   // Position of the light (for point lights), or (0,0,0) for ambient
    Vector3 intensity;  // RGB intensity, usually in [0, 1] after parsing

    // Constructor to initialize a light
    Light(const Vector3& position, const Vector3& intensity);
};

#endif
