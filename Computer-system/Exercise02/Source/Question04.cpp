#include <iostream>
#include <string>

using namespace std;

int main() {
  float floatNumBegin = 3.14159f;
  cout << "Float number at the beginning: " << floatNumBegin << endl;
  int intNum = int(floatNumBegin);
  float floatNumAfter = float(intNum);
  cout << "Float number after conversion: " << floatNumAfter << endl;
  if (floatNumBegin == floatNumAfter) {
    cout << "The float number is the same after conversion." << endl;
  } else {
    cout << "The float number is not the same after conversion." << endl;
  }
  cout << endl;

  int intNumBegin = 5;
  cout << "Int number at the beginning: " << intNumBegin << endl;
  float floatNum = float(intNumBegin);
  int intNumAfter = int(floatNum);
  cout << "Int number after conversion: " << intNumAfter << endl;
  if (intNumBegin == intNumAfter) {
    cout << "The int number is the same after conversion." << endl;
  } else {
    cout << "The int number is not the same after conversion." << endl;
  }
  cout << endl;

  float f1 = 1.4783f;
  float f2 = 5.3974f;
  float f3 = 4.7264f;

  float result1 = (f1 + f2) + f3;
  float result2 = f1 + (f2 + f3);

  cout << "Result of (f1 + f2) + f3: " << result1 << endl;
  cout << "Result of f1 + (f2 + f3): " << result2 << endl;

  if (result1 == result2) {
    cout << "The addition of floating-point numbers is associative." << endl;
  } else {
    cout << "The addition of floating-point numbers is not associative."
         << endl;
  }

  float f = 4.59f;
  int i = (int)(3.14159 * f);
  cout << "The value of i is: " << i << endl;

  f = f + (float)i;
  cout << "The value of f is: " << f << endl;

  cout << "i == (int)((float)i): ";
  if (i == (int)((float)i))
    cout << "true" << endl;
  else
    cout << "false" << endl;

  cout << "i == (int)((double)i): ";
  if (i == (int)((double)i))
    cout << "true" << endl;
  else
    cout << "false" << endl;

  cout << "f == (float)((int)f): ";
  if (f == (float)((int)f))
    cout << "true" << endl;
  else
    cout << "false" << endl;

  cout << "f == (double)((int)f): ";
  if (f == (double)((int)f))
    cout << "true" << endl;
  else
    cout << "false" << endl;
}