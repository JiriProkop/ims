#include <iostream>
#include <fstream>
#include <cstdint>
#include "image.hpp"

void generateImage(Grid grid, int size, std::string fileName) {
    BitmapFileHeader fileHeader;
    BitmapInfoHeader infoHeader;

    int padding = (4 - (size * sizeof(uint8_t) * 3 % 4)) % 4; // padding to ensure liens are multiple of 4 bytes

    fileHeader.type = 0x4D42; // "BM" - the idetifier of bitmap files
    fileHeader.size = sizeof(BitmapFileHeader) + sizeof(BitmapInfoHeader) + (size * size * 3) + (padding * size);
    fileHeader.reserved1 = 0;
    fileHeader.reserved2 = 0;
    fileHeader.offset = sizeof(BitmapFileHeader) + sizeof(BitmapInfoHeader);

    infoHeader.size = sizeof(BitmapInfoHeader);
    infoHeader.width = size;
    infoHeader.height = size;
    infoHeader.planes = 1;
    infoHeader.bitCount = 24; // 24 bits per pixel (8 for R, 8 for G, 8 for B)
    infoHeader.compression = 0;
    infoHeader.imageSize = 0;
    infoHeader.xPixelsPerMeter = 0;
    infoHeader.yPixelsPerMeter = 0;
    infoHeader.colorsUsed = 0;
    infoHeader.colorsImportant = 0;

    // create binary file
    std::ofstream file(fileName, std::ios::binary);

    if (file.is_open()) {
        file.write((const char *)(&fileHeader), sizeof(fileHeader));
        file.write((const char *)(&infoHeader), sizeof(infoHeader));

        // generate the image (rows and columns)
        for (int y = 0; y < size; y++) {
            for (int x = 0; x < size; x++) {
                // load the colors from the grid
                // TODO [y][x] or reversed?
                uint8_t red = grid.getPoint(x, y).getColor().r;
                uint8_t green = grid.getPoint(x, y).getColor().g;
                uint8_t blue = grid.getPoint(x, y).getColor().b;

                // write the colors to the image
                file.write((const char *)(&blue), sizeof(blue));
                file.write((const char *)(&green), sizeof(green));
                file.write((const char *)(&red), sizeof(red));
            }
            if (padding > 0) {
                // write the padding if necessary
                uint8_t pad = 0;
                file.write((const char *)(&pad), padding);
            }
        }

        file.close();
    } else {
        throw std::runtime_error("Cannot create image.");
    }
}