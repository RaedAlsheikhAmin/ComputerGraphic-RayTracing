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
    t = INFINITY;
    closestObject = nullptr;
    bool hit = false;

    for (const auto& obj : objects) {
        float tempT;
        if (obj->intersect(ray, tempT) && tempT < t) {
            t = tempT;
            closestObject = obj;
            hit = true;
        }
    }

    return hit;
}

