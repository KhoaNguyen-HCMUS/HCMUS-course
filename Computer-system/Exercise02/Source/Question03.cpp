#include <cmath>
#include <iostream>
#include <string>

using namespace std;

void removeSpaces(string &str) {
  int n = str.length();
  int j = 0;

  for (int i = 0; i < n; i++) {
    if (str[i] != ' ') {
      str[j] = str[i];
      j++;
    }
  }

  str.erase(j);
}

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
  cout << endl;
}

void forceFloat(float *p, const string &s) {
  unsigned int value = 0;
  for (size_t i = 0; i < s.length(); ++i) {
    value = (value << 1) | (s[i] - '0');
  }

  unsigned int *intPtr = reinterpret_cast<unsigned int *>(p);
  *intPtr = value;
}

float binaryToFloat(string &binary) {
  removeSpaces(binary);
  if (binary.length() != 32) {
    cerr << "Error: Input string must be exactly 32 characters long." << endl;
    return 0.0f;
  }

  float result;
  forceFloat(&result, binary);
  return result;
}

int main() {
  float number = float(1.3e+20);
  cout << "1.3E+20" << endl;
  dumpFloat(&number);

  //--------------------------------------------------------------------------------
  string binary = "0 00000000 00000000000000000000001";
  cout << "Smallest float number greater than 0: " << binaryToFloat(binary)
       << endl;
  cout << "Corresponding binary representation: " << binary << endl;

  //--------------------------------------------------------------------------------
  float zero = 0.0f;
  cout << "Zero: " << zero << endl;
  dumpFloat(&zero);

  unsigned int denormBits = 1;  // Exponent = 0, Significand != 0
  float denorm;
  unsigned int *denormPtr = reinterpret_cast<unsigned int *>(&denorm);
  *denormPtr = denormBits;
  cout << "Denormalized number: " << denorm << endl;
  dumpFloat(&denorm);

  float inf = INFINITY;
  cout << "Infinity number: " << inf << endl;
  dumpFloat(&inf);

  float nan = NAN;
  cout << "NaN number: " << nan << endl;
  dumpFloat(&nan);

  return 0;
}