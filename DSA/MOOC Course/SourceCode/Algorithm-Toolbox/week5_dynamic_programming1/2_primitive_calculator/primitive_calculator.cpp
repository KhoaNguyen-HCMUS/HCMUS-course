#include <algorithm>
#include <iostream>
#include <vector>

std::vector<int> optimal_sequence(int n) {
  std::vector<int> min_operations(n + 1, 0);
  std::vector<int> sequence;

  for (int i = 2; i <= n; ++i) {
    int min_ops = min_operations[i - 1] + 1;
    if (i % 2 == 0) {
      min_ops = std::min(min_ops, min_operations[i / 2] + 1);
    }
    if (i % 3 == 0) {
      min_ops = std::min(min_ops, min_operations[i / 3] + 1);
    }
    min_operations[i] = min_ops;
  }

  for (int i = n; i > 0;) {
    sequence.push_back(i);
    if (i % 3 == 0 && min_operations[i] == min_operations[i / 3] + 1) {
      i /= 3;
    } else if (i % 2 == 0 && min_operations[i] == min_operations[i / 2] + 1) {
      i /= 2;
    } else {
      i -= 1;
    }
  }

  std::reverse(sequence.begin(), sequence.end());
  return sequence;
}

int main() {
  int n;
  std::cin >> n;
  std::vector<int> sequence = optimal_sequence(n);
  std::cout << sequence.size() - 1 << std::endl;
  for (size_t i = 0; i < sequence.size(); ++i) {
    std::cout << sequence[i] << " ";
  }
  return 0;
}