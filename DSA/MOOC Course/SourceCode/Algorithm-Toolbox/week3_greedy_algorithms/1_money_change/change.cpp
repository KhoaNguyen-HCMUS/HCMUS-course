#include <iostream>

int get_change(int n) {
  int count = 0;
  int denominations[] = {10, 5, 1};  // Array of coin denominations

  for (int i : denominations) {
    if (n >= i) {
      int q = n / i;  // Calculate how many coins of denomination i fit into n
      count += q;     // Increase count by the number of coins
      n = n % i;      // Reduce n by the total value of the added coins
      if (n == 0) {
        return count;  // If n is 0, return the total count of coins
      }
    }
  }
  return count;  //
}

int main() {
  int m;
  std::cin >> m;
  std::cout << get_change(m) << '\n';
}
