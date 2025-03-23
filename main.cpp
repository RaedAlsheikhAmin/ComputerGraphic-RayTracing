#include <iostream>
#include <vector>
#include "Camera.h"
#include "Scene.h"
#include "RayTracer.h"
#include "PPMWriter.h"
#include "Sphere.h"
#include "Light.h"
#include "Vector3.h"

int main() {
    // 1. Define Scene with Background Color
    Scene scene(Vector3(0, 0, 0)); // Black background

    // 2. Define Camera Parameters
    Camera camera(
            Vector3(0, 0, 0),      // Camera position
            Vector3(0, 0, -1),     // Gaze direction
            Vector3(0, 1, 0),      // Up vector
            -1, 1, -1, 1,          // Left, right, bottom, top (near plane)
            1,                     // Near distance
            800, 800               // Image width and height
    );

    // 3. Define Materials
    Material redMaterial(
            Vector3(0.1, 0, 0),  // Ambient
            Vector3(1, 0, 0),    // Diffuse (Red)
            Vector3(1, 1, 1),    // Specular (White highlight)
            32,                  // Phong exponent
            Vector3(0.5, 0.5, 0.5) // Mirror reflection (Grayish)
    );

    // 4. Create and Add Objects to Scene
    Sphere* redSphere = new Sphere(Vector3(0, 0, -3), 1, redMaterial);
    scene.addObject(redSphere);

    // 5. Define Light Sources
    Light pointLight(Vector3(5, 5, 0), Vector3(1, 1, 1));  // White Light at (5,5,0)
    scene.addLight(pointLight);

    // 6. Define RayTracer
    RayTracer rayTracer(3, 1e-3);  // Max depth = 3, Shadow ray epsilon = 1e-3

    // 7. Prepare Image Buffer
    std::vector<Vector3> pixels(800 * 800);

    // 8. Ray Tracing Loop
    for (int j = 0; j < 800; j++) {
        for (int i = 0; i < 800; i++) {
            Ray ray = camera.generateRay(i, j);
            pixels[j * 800 + i] = rayTracer.traceRay(ray, scene, 0);
        }
    }

    // 9. Write Image to PPM File
    PPMWriter::writePPM(pixels, 800, 800, "outputRaed1.ppm");

    // 10. Clean Up (Avoid Memory Leaks)
    delete redSphere;

    std::cout << "Rendering complete! Image saved as outputRaed1.ppm" << std::endl;
    return 0;
}
