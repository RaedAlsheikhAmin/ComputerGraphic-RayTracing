//Reference : https://raytracing.github.io/books/RayTracingInOneWeekend.html#outputanimage/theppmimageformat



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
using namespace std;
int main(int argc, char* argv[]) {
    // Ensure the program is run with a filename argument
    // Make sure the user provided the input file name (./raytracer input1.txt)
    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " <input file>" << endl;
        return 1;
    }

    string inputFile = argv[1];// Get scene file from command-line argument
    string outputFile = "output.ppm"; // Output file name

    // Initialize scene
    Scene scene(Vector3(0, 0, 0)); //scene holds all objects, lights, and materials.
    Camera camera; //camera will be initialized by Parser
    RayTracer rayTracer(3, 1e-3); // RayTracer handles casting and shading (max depth = 3, epsilon = 0.001), i am making it manually here, but i am rereading it in the sceneparser

    // Parse the scene from input file
    if (!SceneParser::parseScene(inputFile, scene, camera, rayTracer)) {
        cerr << "Error: Failed to parse scene from " << inputFile << std::endl;
        return -1;
    }

    // Prepare image buffer with the actual camera resolution
    int imageWidth = camera.width;
    int imageHeight = camera.height;
    vector<Vector3> pixels(imageWidth * imageHeight);

    // Ray Tracing Loop
    for (int j = 0; j < imageHeight; j++) {
        for (int i = 0; i < imageWidth; i++) {
            Ray ray = camera.generateRay(i, j);
            pixels[j * imageWidth + i] = rayTracer.traceRay(ray, scene, 0);

        }
    }

    // Write output
    PPMWriter::writePPM(pixels, imageWidth, imageHeight, outputFile);

    cout << "Rendering complete! Image saved as " << outputFile << endl;
    return 0;
}
