#include "PPMWriter.h"

void PPMWriter::writePPM(const std::vector<Vector3>& pixels, int width, int height, const std::string& filename) {
    std::ofstream file(filename);
    file << "P3\n" << width << " " << height << "\n255\n";

    for (const auto& color : pixels) {
        int r = std::min(255, static_cast<int>(color.x * 255));
        int g = std::min(255, static_cast<int>(color.y * 255));
        int b = std::min(255, static_cast<int>(color.z * 255));
        file << r << " " << g << " " << b << "\n";
    }

    file.close();
}
