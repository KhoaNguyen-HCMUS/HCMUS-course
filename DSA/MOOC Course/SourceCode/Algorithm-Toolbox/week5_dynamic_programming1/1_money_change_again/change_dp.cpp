#include <algorithm>
#include <iostream>
#include <vector>

int get_change(int m) {
  std::vector<int> min_coins(m + 1, m + 1);  // Initialize with a large number
  min_coins[0] = 0;  // Base case: 0 coins needed for amount 0

  for (int i = 1; i <= m; ++i) {
    if (i >= 1) min_coins[i] = std::min(min_coins[i], min_coins[i - 1] + 1);
    if (i >= 3) min_coins[i] = std::min(min_coins[i], min_coins[i - 3] + 1);
    if (i >= 4) min_coins[i] = std::min(min_coins[i], min_coins[i - 4] + 1);
  }

  return min_coins[m];
}

int main() {
  int m;
  std::cin >> m;
  std::cout << get_change(m) << '\n';
}