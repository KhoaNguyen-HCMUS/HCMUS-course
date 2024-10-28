#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<bool> stringToBitArray(const string& bitString) {
  vector<bool> bitArray(8);
  for (int i = 0; i < 8; ++i) {
    if (bitString[i] == '0') {
      bitArray[i] = 0;
    } else if (bitString[i] == '1') {
      bitArray[i] = 1;
    } else {
      cerr << "Error: Input string must contain only '0' or '1'." << endl;
      return bitArray;
    }
  }
  return bitArray;
}

vector<bool> addBitArrays(const vector<bool>& a, const vector<bool>& b) {
  vector<bool> result(8);
  int carry = 0;
  for (int i = 7; i >= 0; --i) {
    int sum = a[i] + b[i] + carry;
    result[i] = sum % 2;
    carry = sum / 2;
  }
  return result;
}

vector<bool> subtractBitArrays(const vector<bool>& a, const vector<bool>& b) {
  vector<bool> negB(8);
  int carry = 1;
  for (int i = 7; i >= 0; --i) {
    negB[i] = 1 - b[i];
  }
  negB = addBitArrays(negB, vector<bool>{0, 0, 0, 0, 0, 0, 0, 1});
  return addBitArrays(a, negB);
}

vector<bool> boothMultiplication(const vector<bool>& Q, const vector<bool>& M) {
  vector<bool> A(8, 0);
  vector<bool> multiplicand = M;
  vector<bool> multiplier = Q;
  int Q_1 = 0;
  int k = 8;

  while (k > 0) {
    if (multiplier[7] == 1 && Q_1 == 0) {
      A = subtractBitArrays(A, multiplicand);
    } else if (multiplier[7] == 0 && Q_1 == 1) {
      A = addBitArrays(A, multiplicand);
    }

    Q_1 = multiplier[7];
    for (int i = 7; i > 0; --i) {
      multiplier[i] = multiplier[i - 1];
    }
    multiplier[0] = A[7];
    for (int i = 7; i > 0; --i) {
      A[i] = A[i - 1];
    }
    A[0] = A[1];

    k--;
  }

  vector<bool> result(16);
  for (int i = 0; i < 8; ++i) {
    result[i] = A[i];
    result[i + 8] = multiplier[i];
  }
  return result;
}

vector<bool> negateBitArray(const vector<bool>& bitArray) {
  vector<bool> negated(bitArray.size());
  for (size_t i = 0; i < bitArray.size(); ++i) {
    negated[i] = 1 - bitArray[i];
  }

  vector<bool> one(bitArray.size(), 0);
  one.back() = 1;
  negated = addBitArrays(negated, one);
  return negated;
}

void printVector(vector<bool> a) {
  for (int x : a) cout << x << "";
}

pair<vector<bool>, vector<bool>> divideBitArrays(const vector<bool>& a,
                                                 const vector<bool>& b) {
  vector<bool> Q = a;
  vector<bool> M = b;
  int k = 8;

  if (a[0] == 1) Q = negateBitArray(Q);
  if (b[0] == 1) M = negateBitArray(M);

  vector<bool> A(8, 0);

  while (k > 0) {
    int carry = Q[0];
    for (int i = 0; i < 7; ++i) {
      A[i] = A[i + 1];
      Q[i] = Q[i + 1];
    }
    A[7] = carry;
    Q[7] = 0;

    A = subtractBitArrays(A, M);

    if (A[0] == 1) {
      Q[7] = 0;
      A = addBitArrays(A, M);
    } else {
      Q[7] = 1;
    }

    k--;
  }

  if (a[0] != b[0]) Q = negateBitArray(Q);
  if (a[0] == 1) A = negateBitArray(A);

  return {Q, A};
}

int main() {
  string bitString1, bitString2;
  cout << "Enter the first 8-bit number (in two's complement):  ";
  cin >> bitString1;

  cout << "Enter the second 8-bit number (in two's complement): ";
  cin >> bitString2;

  if (bitString1.size() != 8 || bitString2.size() != 8) {
    cerr << "Error: Input strings must have length 8." << endl;
    return 1;
  }

  vector<bool> bits1 = stringToBitArray(bitString1);
  vector<bool> bits2 = stringToBitArray(bitString2);

  vector<bool> sumBits = addBitArrays(bits1, bits2);
  vector<bool> diffBits = subtractBitArrays(bits1, bits2);
  vector<bool> prodBits = boothMultiplication(bits1, bits2);

  pair<vector<bool>, vector<bool>> divResult = divideBitArrays(bits1, bits2);
  vector<bool> quotBits = divResult.first;
  vector<bool> remBits = divResult.second;

  cout << "Sum: ";
  for (int bit : sumBits) {
    cout << bit;
  }
  cout << endl;

  cout << "Difference: ";
  for (int bit : diffBits) {
    cout << bit;
  }
  cout << endl;

  cout << "Product: ";
  for (int bit : prodBits) {
    cout << bit;
  }
  cout << endl;

  cout << "Quotient: ";
  for (int bit : quotBits) {
    cout << bit;
  }
  cout << endl;

  cout << "Remainder: ";
  for (int bit : remBits) {
    cout << bit;
  }
  cout << endl;
  cout << endl;

  return 0;
}