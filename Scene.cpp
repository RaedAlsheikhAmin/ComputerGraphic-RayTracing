#include "Scene.h"
#include "Vector3.h"
#include <vector>


// Constructor Implementation
Scene::Scene(const Vector3& backgroundColor) : backgroundColor(backgroundColor) {}

void Scene::addObject(Object* obj) {
    objects.push_back(obj);
}

void Scene::addLight(const Light& light) {
    lights.push_back(light);
}

bool Scene::getClosestIntersection(const Ray& ray, float& t, Object*& closestObject) const {
    float closestT = INFINITY;
    Object* hitObject = nullptr;

    for (const auto& obj : objects) {
        float currentT;
        if (obj->intersect(ray, currentT) && currentT < closestT) {
            closestT = currentT;
            hitObject = obj;
        }
    }

    if (hitObject) {
        t = closestT;
        closestObject = hitObject;
        return true;
    }

    return false;
}
