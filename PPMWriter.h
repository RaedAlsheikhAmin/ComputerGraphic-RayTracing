#ifndef PPMWRITER_H
#define PPMWRITER_H

#include <vector>
#include <fstream>
#include "Vector3.h"

class PPMWriter {
public:
    static void writePPM(const std::vector<Vector3>& pixels, int width, int height, const std::string& filename);
};

#endif
