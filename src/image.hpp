#include <iostream>
#include <cstdint>
#include "grid.hpp"

#ifndef IMAGE_HPP
#define IMAGE_HPP

#define DEFAULT_IMAGE_SIZE 120

// pragma pack for correct alignment
#pragma pack(push, 1)

/**
 * A structure for describing the bitmap file header
*/
struct BitmapFileHeader {
    uint16_t type;
    uint32_t size;
    uint16_t reserved1;
    uint16_t reserved2;
    uint32_t offset;
};

/**
 * A structure for describing the bitmap file info.
*/
struct BitmapInfoHeader {
    uint32_t size;
    int32_t width;
    int32_t height;
    uint16_t planes;
    uint16_t bitCount;
    uint32_t compression;
    uint32_t imageSize;
    int32_t xPixelsPerMeter;
    int32_t yPixelsPerMeter;
    uint32_t colorsUsed;
    uint32_t colorsImportant;
};
#pragma pack(pop)

/**
 * A function for generating the crossroad background into the grid
 * 
 * @param grid The grid to generate the background. MUST have the size of 120!
*/
void generateCrossroadBackgroud(Grid *grid);

/**
 * A function for generating a bitmap image from the grid.
 * 
 * @param grid The grid to generate the image from.
 * @param size The size of the grid.
*/
void generateImage(Grid grid, int size, std::string fileName);

#endif