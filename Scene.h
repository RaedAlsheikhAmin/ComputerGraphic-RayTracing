#ifndef INC_477HW1_SCENE_H
#define INC_477HW1_SCENE_H

#include <vector>
#include "Object.h"
#include "Light.h"
#include "Vector3.h"

class Scene {
public:
    std::vector<Object*> objects;
    std::vector<Light> lights;
    Vector3 backgroundColor;

    Scene(const Vector3& backgroundColor);

    void addObject(Object* obj);
    void addLight(const Light& light);
    bool getClosestIntersection(const Ray& ray, float& t, Object*& closestObject) const;
};

#endif
