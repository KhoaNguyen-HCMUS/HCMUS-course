#include <iostream>

int gcd(int a, int b) {
  while (a * b != 0) {
    if (a > b) {
      a = a % b;
    } else {
      b = b % a;
    }
  }
  return a + b;
}

long long lcm(int a, int b) { return (long long)a * b / gcd(a, b); }

int main() {
  int a, b;
  std::cin >> a >> b;
  std::cout << lcm(a, b) << std::endl;
  return 0;
}
