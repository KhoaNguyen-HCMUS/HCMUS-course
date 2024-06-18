#include "bitmap.h"

int main(int argc, char **argv) {
  int n = argc;
  int x = 1, y = 1;
  char *sourceFile = argv[1];
  for (int i = 0; i < n; i++) {
    if (strcmp(argv[i], "-h") == 0) {
      y = atoi(argv[i + 1]);
    }
    if (strcmp(argv[i], "-w") == 0) {
      x = atoi(argv[i + 1]);
    }
  }
  BMPFile file;
  FILE *f = fopen(sourceFile, "rb");
  ReadFile(f, file);
  TransferToPixelMatrix(file);
  // PrintInfo(f, file);
  // PrintPixelArray(f, file);
  CutBMPFile(f, file, y, x, sourceFile);
  ReleaseMemory(file);
  fclose(f);
}