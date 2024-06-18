#include "bitmap.h"

void ReadFile(FILE* f, BMPFile& file) {
  fread(file.Signature.data, sizeof(Sign), 1, f);
  fread(&file.Header, sizeof(BmpHeader), 1, f);
  fread(&file.DIB, sizeof(BmpDIBFormat), 1, f);

  // Calculate padding
  file.PixelArray.Padding =
      (4 - (file.DIB.ImageWidth * (file.DIB.ColorDepth / 8) % 4)) % 4;
  int size = file.DIB.ImageWidth * file.DIB.ImageHeight;

  // Allocate memory for pixel array
  file.PixelArray.Pixels = new Pixel[size];
  unsigned char paddings[4];

  // Read pixel array
  int Height = file.DIB.ImageHeight;
  int Width = file.DIB.ImageWidth;
  for (int i = 0; i < Height; ++i) {
    for (int j = 0; j < Width; ++j) {
      fread(&file.PixelArray.Pixels[(Height - i - 1) * Width + j],
            sizeof(Pixel), 1, f);
    }
    fread(paddings, sizeof(unsigned char), file.PixelArray.Padding, f);
  }
}

void TransferToPixelMatrix(BMPFile& file) {
  int Height = file.DIB.ImageHeight;
  int Width = file.DIB.ImageWidth;
  file.PixelArray.PixelMatrix = new Pixel*[Height];
  for (int i = 0; i < Height; i++) {
    file.PixelArray.PixelMatrix[i] = new Pixel[Width];
    for (int j = 0; j < Width; j++) {
      file.PixelArray.PixelMatrix[i][j] = file.PixelArray.Pixels[i * Width + j];
    }
  }
}

void PrintInfo(FILE* f, BMPFile file) {
  cout << "---HEADER---" << endl;
  cout << "Signature              : " << file.Signature.data[0]
       << file.Signature.data[1] << endl;
  cout << "File size              : " << file.Header.Filesize << endl;
  cout << "Reserved 1             : " << file.Header.Reserved1 << endl;
  cout << "Reserved 2             : " << file.Header.Reserved2 << endl;
  cout << "Pixel Array byte offset: " << file.Header.PixelArrayOffset << endl
       << endl;
  cout << "---DIB Format---" << endl;
  cout << "DIB size                                 : " << file.DIB.DIBsize
       << endl;
  cout << "Image width                              : " << file.DIB.ImageWidth
       << endl;
  cout << "Image height                             : " << file.DIB.ImageHeight
       << endl;
  cout << "Color planes                             : " << file.DIB.ColorPlanes
       << endl;
  cout << "Color depth                              : " << file.DIB.ColorDepth
       << endl;
  cout << "Compression algorithm                    : "
       << file.DIB.CompressionAlgorithm << endl;
  cout << "Pixel Array size                         : "
       << file.DIB.PixelArraySize << endl;
  cout << "Horizontal resolution                    : "
       << file.DIB.HorizontalResolution << endl;
  cout << "Vertical resolution                      : "
       << file.DIB.VerticalResolution << endl;
  cout << "Number of colors in Color Table          : " << file.DIB.NumberColors
       << endl;
  cout << "Number of important colors in Color Table: "
       << file.DIB.NumberImportantColors << endl
       << endl;
}

void ReleaseMemory(BMPFile& file) {
  delete[] file.PixelArray.Pixels;
  for (int i = 0; i < file.DIB.ImageHeight; i++) {
    delete[] file.PixelArray.PixelMatrix[i];
  }
  delete[] file.PixelArray.PixelMatrix;
}

void PrintPixelArray(BMPFile file) {
  for (int i = 0; i < file.DIB.ImageHeight; i++) {
    for (int j = 0; j < file.DIB.ImageWidth; j++) {
      Pixel p = file.PixelArray.PixelMatrix[i][j];
      cout << "Pixel at (" << i << ", " << j << "): "
           << "R=" << (int)p.r << ", G=" << (int)p.g << ", B=" << (int)p.b
           << '\n';
    }
  }
}

void CutBMPFile(FILE* f, BMPFile file, int y, int x, char* sourceFile) {
  if (y > file.DIB.ImageHeight) {
    cout << "y is greater than the height of the image" << endl;
    return;
  }
  if (x > file.DIB.ImageWidth) {
    cout << "x is greater than the width of the image" << endl;
    return;
  }

  // Create the name of the sub file
  int index = 0;
  for (int i = strlen(sourceFile) - 1; i >= 0; i--) {
    if (sourceFile[i] == '/') {
      index = i;
      break;
    }
  }

  char* subFileName = new char[strlen(sourceFile) + 8];
  strcpy(subFileName, sourceFile);
  for (int i = strlen(subFileName) - 1; i >= 0; i--) {
    if (subFileName[i] == '.') {
      index = i;
      break;
    }
  }
  strcpy(subFileName + index, ".part00.bmp\0");
  int n = strlen(subFileName);
  int count = 0;
  // Calculate information about subfile
  int subFileHeight = file.DIB.ImageHeight / y;
  int subFileWidth = file.DIB.ImageWidth / x;

  int lastSubFileWidth =
      file.DIB.ImageWidth - (x - 1) * (file.DIB.ImageWidth / x);
  int lastSubFileHeight =
      file.DIB.ImageHeight - (y - 1) * (file.DIB.ImageHeight / y);
  int subFilePadding = (4 - (subFileWidth * (file.DIB.ColorDepth / 8) % 4)) % 4;
  int lastSubFilePadding =
      (4 - (lastSubFileWidth * (file.DIB.ColorDepth / 8) % 4)) % 4;
  int subFileSize = subFileHeight * subFileWidth * sizeof(Pixel) +
                    subFilePadding * subFileHeight;

  for (int i = 0; i < y; i++) {
    for (int j = 0; j < x; j++) {
      BMPFile file_sub = file;
      file_sub.DIB.ImageWidth = subFileWidth;
      file_sub.DIB.ImageHeight = subFileHeight;
      file_sub.DIB.PixelArraySize = subFileSize;
      file_sub.PixelArray.Padding = subFilePadding;
      if (i == y - 1 && j == x - 1) {
        // Adjust the height and width for the last subfile
        file_sub.DIB.ImageHeight = lastSubFileHeight;
        file_sub.DIB.ImageWidth = lastSubFileWidth;
        file_sub.DIB.PixelArraySize =
            lastSubFileHeight *
            (lastSubFileWidth * sizeof(Pixel) + subFilePadding);

      } else if (i == y - 1 && j != x - 1) {
        // Adjust the height for the last row of subfiles
        file_sub.DIB.ImageHeight = lastSubFileHeight;
        file_sub.DIB.PixelArraySize =
            lastSubFileHeight * (subFileWidth * sizeof(Pixel) + subFilePadding);

      } else if (j == x - 1 && i != y - 1) {
        // Adjust the width for the last column of subfiles
        file_sub.DIB.ImageWidth = lastSubFileWidth;
        file_sub.PixelArray.Padding =
            (4 - (lastSubFileWidth * (file.DIB.ColorDepth / 8) % 4)) % 4;
        file_sub.DIB.PixelArraySize =
            subFileHeight *
            (lastSubFileWidth * sizeof(Pixel) + file_sub.PixelArray.Padding);
      }
      count++;
      subFileName[n - 6] = (char)(48 + count / 10);
      subFileName[n - 5] = (char)(48 + count % 10);
      FILE* subFile = fopen(subFileName, "wb");
      fwrite(file_sub.Signature.data, sizeof(Sign), 1, subFile);
      fwrite(&file_sub.Header, sizeof(BmpHeader), 1, subFile);
      fwrite(&file_sub.DIB, sizeof(BmpDIBFormat), 1, subFile);
      if (i == y - 1 && j == x - 1) {
        // Write pixels for the last subfile
        for (int k = (i * subFileHeight + lastSubFileHeight) - 1;
             k >= i * subFileHeight; k--) {
          for (int l = j * subFileWidth; l < j * subFileWidth + subFileWidth;
               l++) {
            fwrite(&file.PixelArray.PixelMatrix[k][l], sizeof(Pixel), 1,
                   subFile);
          }
          for (int l = 0; l < lastSubFilePadding; l++) {
            fwrite("0", sizeof(unsigned char), 1, subFile);
          }
        }
      } else if (i == y - 1 && j != x - 1) {
        // Write pixels for the last row of subfiles
        for (int k = (i * subFileHeight + lastSubFileHeight) - 1;
             k >= i * subFileHeight; k--) {
          for (int l = j * subFileWidth; l < (j + 1) * subFileWidth; l++) {
            fwrite(&file.PixelArray.PixelMatrix[k][l], sizeof(Pixel), 1,
                   subFile);
          }
          for (int l = 0; l < subFilePadding; l++) {
            fwrite("0", sizeof(unsigned char), 1, subFile);
          }
        }
      } else if (j == x - 1 && i != y - 1) {
        // Write pixels for the last column of subfiles
        for (int k = (i + 1) * subFileHeight - 1; k >= i * subFileHeight; k--) {
          for (int l = j * subFileWidth;
               l < j * subFileWidth + lastSubFileWidth; l++) {
            fwrite(&file.PixelArray.PixelMatrix[k][l], sizeof(Pixel), 1,
                   subFile);
          }
          for (int l = 0; l < lastSubFilePadding; l++) {
            fwrite("0", sizeof(unsigned char), 1, subFile);
          }
        }
      } else {
        // Write pixels for the other files
        for (int k = (i + 1) * subFileHeight - 1; k >= i * subFileHeight; k--) {
          for (int l = j * subFileWidth; l < (j + 1) * subFileWidth; l++) {
            fwrite(&file.PixelArray.PixelMatrix[k][l], sizeof(Pixel), 1,
                   subFile);
          }
          for (int l = 0; l < subFilePadding; l++) {
            fwrite("0", sizeof(unsigned char), 1, subFile);
          }
        }
      }

      fclose(subFile);
    }
  }
  delete[] subFileName;
  cout << "Split file successfully!" << endl;
}