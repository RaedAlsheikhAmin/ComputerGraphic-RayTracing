//
// Created by Raed Alsheikh Amin on 3/07/2025.
//This class was done fully using the Slides
#ifndef INC_477HW1_CAMERA_H
#define INC_477HW1_CAMERA_H

#include "Vector3.h"
#include "Ray.h"

/**
 * Camera class handles the camera setup and primary ray generation.
 * We use this to figure out what direction each pixel is "looking" at.
 * Based on slide 23–26 (Ray Generation & Camera coordinate system)
 */
class Camera {
public:
    Vector3 position; // Where the camera is placed (eye position)

    // The gaze direction is where the camera is pointing.
    // 'up' is the tilt of the camera (used to orient it correctly),
    // and u, v, w are the camera's coordinate basis.
    Vector3 gaze, up, u, v, w;

    // These define the viewing window or image plane bounds.
    float left, right, bottom, top;

    // Distance from the camera to the image (projection) plane
    float nearDistance;

    // Image resolution (width x height)
    int width, height;

    /**
     * Default constructor.
     * Not really used often but defined just in case we create a camera and assign later.
     */
    Camera();

    /**
     * Full constructor.
     * This takes all camera parameters from the scene file and sets up everything.
     * It also internally computes the u, v, w vectors so we can shoot rays in the right directions.
     *
     * @param position - camera position (eye)
     * @param gaze - gaze direction (where it's looking)
     * @param up - up direction (to orient the image upright)
     * @param left, right, bottom, top - bounds of the viewing plane
     * @param nearDistance - distance to the viewing plane
     * @param width, height - resolution of the output image
     */
    Camera(Vector3 position, Vector3 gaze, Vector3 up,
           float left, float right, float bottom, float top,
           float nearDistance, int width, int height);

    /**
     * Generates a primary ray from the camera through pixel (i, j)
     * This is the core of ray tracing – for every pixel, we shoot a ray
     * and check what it hits. That’s how we know what color to paint that pixel.
     *
     * Reference: Slide 26 (Ray Generation Formula)
     *
     * @param i - x pixel index
     * @param j - y pixel index
     * @return Ray that goes from the camera to the pixel's corresponding point in space
     */
    Ray generateRay(int i, int j) const;
};

#endif
