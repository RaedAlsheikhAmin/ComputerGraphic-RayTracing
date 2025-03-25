#include <iostream>
#include <vector>
#include "Camera.h"
#include "Scene.h"
#include "RayTracer.h"
#include "PPMWriter.h"
#include "Sphere.h"
#include "Light.h"
#include "Vector3.h"
#include "SceneParser.h"


int main() {
    Scene scene(Vector3(0, 0, 0));
    Camera camera(Vector3(0, 0, 0), Vector3(0, 0, -1), Vector3(0, 1, 0), -1, 1, -1, 1, 1, 800, 800);
    RayTracer rayTracer(3, 1e-3);
    std::vector<Material> materials; // Store materials separately

    if (!SceneParser::parseScene("../input1.txt", scene, camera, rayTracer, materials)) {
        return -1;
    }

    // Prepare image buffer
    std::vector<Vector3> pixels(800 * 800);

    // Ray Tracing Loop
    for (int j = 0; j < 800; j++) {
        for (int i = 0; i < 800; i++) {
            Ray ray = camera.generateRay(i, j);
            pixels[j * 800 + i] = rayTracer.traceRay(ray, scene, 0);
        }
    }

    // Write output
    PPMWriter::writePPM(pixels, 800, 800, "../outputtest1.ppm");

    std::cout << "Rendering complete! Image saved as outputtest1.ppm" << std::endl;
    return 0;
}
