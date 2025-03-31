//
// Created by Raed Alsheikh Amin on 3/09/2025.
// Reference: https://raytracing.github.io/books/RayTracingInOneWeekend.html#outputanimage/theppmimageformat


#include "Light.h"

/**
 * Constructor for the Light class.
 * A light has a position in the scene (x, y, z) and an intensity (r, g, b).
 *
 * - For ambient light (Slide 27), we just pass position as (0, 0, 0).
 * - For point lights (Slides 28–32), we use actual positions and intensities.
 *
 * The intensity values are usually normalized (divided by 255 )
 * during parsing so they're in the [0, 1] range.
 */
Light::Light(const Vector3& position, const Vector3& intensity)
        : position(position), intensity(intensity) {}
