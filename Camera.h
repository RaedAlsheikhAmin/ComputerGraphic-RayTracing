#ifndef CAMERA_H
#define CAMERA_H

#include "Vector3.h"
#include "Ray.h"

class Camera {
public:
    Vector3 position, gaze, up, right;
    float nearPlane[4];  // left, right, bottom, top
    float nearDistance;
    int width, height;

    Camera(const Vector3& position, const Vector3& gaze, const Vector3& up, float l, float r, float b, float t, float d, int w, int h);
    Ray generateRay(int i, int j) const;
};

#endif
