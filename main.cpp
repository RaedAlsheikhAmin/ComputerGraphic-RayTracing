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

int main(int argc, char* argv[]) {
    // Ensure the program is run with a filename argument
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <input file>" << std::endl;
        return 1;
    }

    std::string inputFile = argv[1];
    std::string outputFile = "outputtest222222.ppm"; // Output file name

    // Initialize scene
    Scene scene(Vector3(0, 0, 0));
    Camera camera;
    RayTracer rayTracer(3, 1e-3);
    std::vector<Material> materials;

    // Parse the scene from input file
    if (!SceneParser::parseScene(inputFile, scene, camera, rayTracer)) {
        std::cerr << "Error: Failed to parse scene from " << inputFile << std::endl;
        return -1;
    }

    // Prepare image buffer with the actual camera resolution
    int imageWidth = camera.width;
    int imageHeight = camera.height;
    std::vector<Vector3> pixels(imageWidth * imageHeight);

    // Ray Tracing Loop
    for (int j = 0; j < imageHeight; j++) {
        for (int i = 0; i < imageWidth; i++) {
            Ray ray = camera.generateRay(i, j);
            pixels[j * imageWidth + i] = rayTracer.traceRay(ray, scene, 0);
        }
    }

    // Write output
    PPMWriter::writePPM(pixels, imageWidth, imageHeight, outputFile);

    std::cout << "Rendering complete! Image saved as " << outputFile << std::endl;
    return 0;
}
