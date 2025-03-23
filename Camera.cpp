#include "Camera.h"

Camera::Camera(const Vector3& position, const Vector3& gaze, const Vector3& up, float l, float r, float b, float t, float d, int w, int h)
        : position(position), gaze(gaze.normalize()), up(up.normalize()), nearDistance(d), width(w), height(h) {
    right = gaze.cross(up).normalize();
    nearPlane[0] = l; nearPlane[1] = r; nearPlane[2] = b; nearPlane[3] = t;
}

Ray Camera::generateRay(int i, int j) const {
    float u = (nearPlane[1] - nearPlane[0]) * (i + 0.5f) / width + nearPlane[0];
    float v = (nearPlane[3] - nearPlane[2]) * (j + 0.5f) / height + nearPlane[2];
    Vector3 direction = gaze * nearDistance + right * u - up * v;
    return Ray(position, direction);
}
