#include <iostream>
#include <vector>

using std::vector;

vector<int> optimal_summands(int n) {
  vector<int> summands;
  for (int i = 0; i < n; i++) {
    if (n == 0) {
      break;
    }
    if (n <= 2 * (i + 1)) {
      summands.push_back(n);
      break;
    }
    summands.push_back(i + 1);
    n -= (i + 1);
  }
  return summands;
}

int main() {
  int n;
  std::cin >> n;
  vector<int> summands = optimal_summands(n);
  std::cout << summands.size() << '\n';
  for (size_t i = 0; i < summands.size(); ++i) {
    std::cout << summands[i] << ' ';
  }
}
