#include <iostream>
#include <fstream>
#include <cstdint>
#include "grid.hpp"
#include "image.hpp"

void generateCrossroadBackgroud(Grid *grid) {
    // set general gray backgroud
    for (int y = 0; y < DEFAULT_IMAGE_SIZE; y++) {
        for (int x = 0; x < DEFAULT_IMAGE_SIZE; x++) {
            Point point(60, 60, 60);
            point.clearPoint();
            grid->setPoint(x, y, point);
        }
    }

    // set the "Purkynova" street
    const int PURKYNOVA_START = 48;
    const int PURKYNOVA_WIDTH = 24;
    for (int y = 0; y < DEFAULT_IMAGE_SIZE; y++) {
        for (int x = PURKYNOVA_START; x < PURKYNOVA_START + PURKYNOVA_WIDTH; x++) {
            Point point(120, 120, 120);
            point.clearPoint();
            grid->setPoint(x, y, point);
        }
    }

    // set the "Skacelova" street
    const int SKACELOVA_START = 46;
    const int SKACELOVA_WIDTH = 28;
    for (int y = SKACELOVA_START; y < SKACELOVA_START + SKACELOVA_WIDTH; y++) {
        for (int x = 0; x < DEFAULT_IMAGE_SIZE; x++) {
            Point point(120, 120, 120);
            point.clearPoint();
            grid->setPoint(x, y, point);
        }
    }
    
    // set the crosswalks on the streets
    const int CROSSWALK_WIDTH = 10;
    for (int y = SKACELOVA_START + SKACELOVA_WIDTH + 8; y < SKACELOVA_START + SKACELOVA_WIDTH + 8 + CROSSWALK_WIDTH; y++) {
        for (int x = PURKYNOVA_START; x < PURKYNOVA_START + PURKYNOVA_WIDTH; x++) {
            Point point(200, 200, 200);
            point.clearPoint();
            grid->setPoint(x, y, point);
        }
    }
    for (int y = SKACELOVA_START - 4 - CROSSWALK_WIDTH; y < SKACELOVA_START - 4; y++) {
        for (int x = PURKYNOVA_START; x < PURKYNOVA_START + PURKYNOVA_WIDTH; x++) {
            Point point(200, 200, 200);
            point.clearPoint();
            grid->setPoint(x, y, point);
        }
    }
    for (int y = SKACELOVA_START; y < SKACELOVA_START + SKACELOVA_WIDTH; y++) {
        for (int x = PURKYNOVA_START - 8 - CROSSWALK_WIDTH; x < PURKYNOVA_START - 8; x++) {
            Point point(200, 200, 200);
            point.clearPoint();
            grid->setPoint(x, y, point);
        }
    }
    for (int y = SKACELOVA_START; y < SKACELOVA_START + SKACELOVA_WIDTH; y++) {
        for (int x = PURKYNOVA_START + PURKYNOVA_WIDTH + 4; x < PURKYNOVA_START + PURKYNOVA_WIDTH + 4 + CROSSWALK_WIDTH; x++) {
            Point point(200, 200, 200);
            point.clearPoint();
            grid->setPoint(x, y, point);
        }
    }
}

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