//
// Created by Raed Alsheikh Amin on 3/14/2025.
//


#include "PPMWriter.h"
#include <fstream>
#include <iostream>

/*
 * This function writes the final image buffer to a PPM file (ASCII format).
 * it's essential to visualize what our ray tracer is doing behind the scenes.
 */
void PPMWriter::writePPM(const std::vector<Vector3>& pixels, int width, int height, const std::string& filename) {
    std::ofstream file(filename);

    if (!file.is_open()) {//Just checking if the file is openning or not
        std::cerr << "Error: Could not open " << filename << " for writing." << std::endl;
        return;
    }

    std::cout << "Writing PPM image: " << filename << std::endl;

    // PPM header
    file << "P3\n" << width << " " << height << "\n255\n";

    // Loop over all pixels in the image buffer and convert from [0,1] float range to [0,255] integer range
    for (const auto& color : pixels) {
        // Clamp values just in case some color went out of bounds
        int r = std::min(255, std::max(0, static_cast<int>(color.x * 255)));
        int g = std::min(255, std::max(0, static_cast<int>(color.y * 255)));
        int b = std::min(255, std::max(0, static_cast<int>(color.z * 255)));

        file << r << " " << g << " " << b << "\n";
    }

    file.close();
    std::cout << "PPM file successfully written: " << filename << std::endl;// as success message to make sure the file exists.
}
