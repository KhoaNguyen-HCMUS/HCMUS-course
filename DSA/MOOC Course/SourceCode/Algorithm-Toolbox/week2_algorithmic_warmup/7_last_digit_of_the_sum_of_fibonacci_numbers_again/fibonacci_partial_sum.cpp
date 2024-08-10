#include <iostream>
#include <vector>

int get_fibonacci_last_digit_fast(long long n) {
  if (n <= 1) return n;

  int previous = 0;
  int current = 1;

  for (long long i = 0; i < n - 1; ++i) {
    int tmp_previous = previous;
    previous = current;
    current = (tmp_previous + current) % 10;
  }

  return current;
}

int fibonacci_partial_sum_fast(long long from, long long to) {
  int sum_to = get_fibonacci_last_digit_fast((to + 2) % 60);
  int sum_from = get_fibonacci_last_digit_fast((from + 1) % 60);
  int result = sum_to - sum_from;
  if (result < 0) result += 10;
  return result;
}

int main() {
  long long from, to;
  std::cin >> from >> to;
  std::cout << fibonacci_partial_sum_fast(from, to) << '\n';
  return 0;
}