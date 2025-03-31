#include "Camera.h"

Camera::Camera()
        : position(Vector3(0, 0, 0)), gaze(Vector3(0, 0, -1)), up(Vector3(0, 1, 0)),
          left(-1), right(1), bottom(-1), top(1), nearDistance(1), width(800), height(800) {

    w = (-gaze).normalize();
    u = up.cross(w).normalize();
    v = w.cross(u).normalize();
}

Camera::Camera(Vector3 position, Vector3 gaze, Vector3 up,
               float left, float right, float bottom, float top,
               float nearDistance, int width, int height)
        : position(position), gaze(gaze.normalize()), up(up.normalize()),
          left(left), right(right), bottom(bottom), top(top),
          nearDistance(nearDistance), width(width), height(height) {

    w = (-gaze).normalize();
    u = up.cross(w).normalize();
    v = w.cross(u).normalize();
}

Ray Camera::generateRay(int i, int j) const {
    float su = ((right - left) * (i + 0.5f)) / width;
    float sv = ((top - bottom) * (j + 0.5f)) / height;

    Vector3 m = position + gaze * nearDistance;
    Vector3 q = m + u * left + v * top;

    Vector3 s = q + u * su - v * sv;
    Vector3 dir = (s - position).normalize();

    return Ray(position, dir);
}
