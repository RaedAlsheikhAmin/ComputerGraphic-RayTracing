#include "PPMWriter.h"
#include <fstream>
#include <iostream>

void PPMWriter::writePPM(const std::vector<Vector3>& pixels, int width, int height, const std::string& filename) {
    std::ofstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error: Could not open " << filename << " for writing." << std::endl;
        return;
    }

    std::cout << "Writing PPM image: " << filename << std::endl;

    file << "P3\n" << width << " " << height << "\n255\n";

    for (const auto& color : pixels) {
        int r = std::min(255, std::max(0, static_cast<int>(color.x * 255)));
        int g = std::min(255, std::max(0, static_cast<int>(color.y * 255)));
        int b = std::min(255, std::max(0, static_cast<int>(color.z * 255)));

        file << r << " " << g << " " << b << "\n";
    }

    file.close();
    std::cout << "PPM file successfully written: " << filename << std::endl;
}
