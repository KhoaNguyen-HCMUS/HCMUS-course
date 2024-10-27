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
  string binary;
  cout << "Enter the binary representation of the floating point number "
          "(32-bit): ";
  getline(cin, binary);

  float number = binaryToFloat(binary);
  cout << "Corresponding (single) floating point number: " << number << endl;

  return 0;
}