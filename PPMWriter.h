//
// Created by Raed Alsheikh Amin on 3/14/2025.
//


#ifndef INC_477HW1_PPMWRITER_H
#define INC_477HW1_PPMWRITER_H

#include <vector>
#include <fstream>
#include "Vector3.h"

/*
 * Responsible for saving the final rendered image as a PPM file.
 * Just takes the pixel buffer and outputs a simple plain-text image.
 */
class PPMWriter {
public:
    static void writePPM(const std::vector<Vector3>& pixels, int width, int height, const std::string& filename);
};

#endif
