#ifndef BITMAP_H
#define BITMAP_H

#include <stdint.h>
#include <stdlib.h>

#include <cstring>
#include <iostream>
using namespace std;
struct Sign {
  char data[2];
};

struct BmpHeader {
  uint32_t Filesize;
  uint16_t Reserved1;
  uint16_t Reserved2;
  uint32_t PixelArrayOffset;
};

struct BmpDIBFormat {
  uint32_t DIBsize;
  uint32_t ImageWidth;
  uint32_t ImageHeight;
  uint16_t ColorPlanes;
  uint16_t ColorDepth;
  uint32_t CompressionAlgorithm;
  uint32_t PixelArraySize;
  uint32_t HorizontalResolution;
  uint32_t VerticalResolution;
  uint32_t NumberColors;
  uint32_t NumberImportantColors;
};

struct Pixel {
  uint8_t b;
  uint8_t g;
  uint8_t r;
};

struct PixelArrayFormat {
  Pixel *Pixels;
  Pixel **PixelMatrix;
  int Padding;
};

struct BMPFile {
  Sign Signature;
  BmpHeader Header;
  BmpDIBFormat DIB;
  PixelArrayFormat PixelArray;
};

void ReadFile(FILE *f, BMPFile &file);
void PrintInfo(FILE *f, BMPFile file);
void TransferToPixelMatrix(BMPFile &file);
void PrintPixelArray(BMPFile file);
void CutBMPFile(FILE *f, BMPFile file, int y, int x, char *sourceFile);
void ReleaseMemory(BMPFile &file);
#endif