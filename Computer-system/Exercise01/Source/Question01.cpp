#include <iostream>
#include <vector>

using namespace std;

void printBinaryRepresentation(int X) {
  int numBits = (X >= -128 && X <= 127) ? 8 : 32;

  cout << "Binary representation of " << X << " by Two Complement is: ";
  for (int i = numBits - 1; i >= 0; --i) {
    cout << ((X >> i) & 1);
  }
  cout << endl;
}

void constructIntegerFromArray(const vector<bool>& A) {
  if (A.size() != 32) {
    cerr << "Array A must have exactly 32 elements." << endl;
    return;
  }

  int X = 0;
  for (int i = 0; i < 32; ++i) {
    if (A[i] == 1) {
      X |= (1 << (31 - i));
    }
  }

  cout << "Constructed integer from array is: " << X << endl;
}

int main() {
  int X;
  cout << "Enter an integer X: ";
  cin >> X;
  printBinaryRepresentation(X);

  vector<bool> A(32);
  cout << "Enter an array A of 32 elements: ";
  for (int i = 0; i < 32; ++i) {
    cin >> A[i];
  }
  A = {0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1,
       0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1};

  constructIntegerFromArray(A);

  return 0;
}