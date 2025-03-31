#ifndef INC_477HW1_CAMERA_H
#define INC_477HW1_CAMERA_H

#include "Vector3.h"
#include "Ray.h"

class Camera {
public:
    Vector3 position;
    Vector3 gaze, up, u, v, w;
    float left, right, bottom, top;
    float nearDistance;
    int width, height;

    // Default constructor
    Camera();

    // Full constructor
    Camera(Vector3 position, Vector3 gaze, Vector3 up,
           float left, float right, float bottom, float top,
           float nearDistance, int width, int height);

    Ray generateRay(int i, int j) const;
};

#endif
