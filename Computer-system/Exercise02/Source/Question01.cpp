#include <iostream>

using namespace std;

void dumpFloat(float *p) {
  unsigned int *intPtr = reinterpret_cast<unsigned int *>(p);
  unsigned int value = *intPtr;

  unsigned int sign = (value >> 31) & 1;

  unsigned int exponent = (value >> 23) & 255;

  unsigned int significand = value & 8388607;

  cout << "Corresponding binary representation: ";
  cout << sign << " ";
  for (int i = 7; i >= 0; --i) {
    cout << ((exponent >> i) & 1);
  }
  cout << " ";
  for (int i = 22; i >= 0; --i) {
    cout << ((significand >> i) & 1);
  }
  cout << endl;
}

int main() {
  float number;
  cout << "Enter floating-point (32-bit): ";
  cin >> number;

  dumpFloat(&number);

  return 0;
}