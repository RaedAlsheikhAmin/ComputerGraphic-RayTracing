//
// Created by Raed Alsheikh Amin on 3/07/2025.
//This class was done fully using the slides
#include "Camera.h"

/**
 * Default constructor.
 * This just sets up a basic forward-facing camera at the origin with default settings.
 * I am just using it in case of hardcoding some values that I didn't parse from the file, but then I ignored it.
 */
Camera::Camera()
        : position(Vector3(0, 0, 0)), gaze(Vector3(0, 0, -1)), up(Vector3(0, 1, 0)),
          left(-1), right(1), bottom(-1), top(1), nearDistance(1), width(800), height(800) {

    // Setting up the camera's coordinate basis (u, v, w)
    // w is the direction the camera is looking *away* from (opposite of gaze)
    w = (-gaze).normalize();

    // u is "right" vector: cross of up × w (camera's right)
    u = up.cross(w).normalize();

    // v is the final "up" vector after orthonormalizing
    v = w.cross(u).normalize();
}

/**
 * Full constructor.
 * This is called from the parser using actual scene file values.
 */
Camera::Camera(Vector3 position, Vector3 gaze, Vector3 up,
               float left, float right, float bottom, float top,
               float nearDistance, int width, int height)
        : position(position), gaze(gaze.normalize()), up(up.normalize()),
          left(left), right(right), bottom(bottom), top(top),
          nearDistance(nearDistance), width(width), height(height) {

    // Same coordinate basis setup as above
    w = (-gaze).normalize();
    u = up.cross(w).normalize();
    v = w.cross(u).normalize();
}

/**
 * This function generates a primary ray from the camera to a pixel (i, j).
 * This is the fundamental part of ray tracing – every pixel shoots a ray.
 *
 * Reference: Slide 26 – “Ray Generation” (how to compute direction of the ray).
 */
Ray Camera::generateRay(int i, int j) const {
    // su and sv are the normalized pixel offsets in the image plane
    // We add 0.5 to sample at the center of the pixel
    float su = ((right - left) * (i + 0.5f)) / width;
    float sv = ((top - bottom) * (j + 0.5f)) / height;

    // m is the center of the near plane
    Vector3 m = position + gaze * nearDistance;

    // q is the top-left corner of the image plane
    Vector3 q = m + u * left + v * top;

    // s is the actual position on the image plane corresponding to pixel (i, j)
    Vector3 s = q + u * su - v * sv;

    // Direction of the ray from the camera origin to pixel center
    Vector3 dir = (s - position).normalize();

    return Ray(position, dir);  // This is the ray we will trace!
}
