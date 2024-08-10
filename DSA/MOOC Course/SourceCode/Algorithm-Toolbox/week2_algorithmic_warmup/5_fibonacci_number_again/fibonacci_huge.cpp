#include <iostream>

long long get_pisano_period_length(long long m) {
  long long previous = 0, current = 1, tmp_previous;
  for (int i = 0; i < m * m; i++) {
    tmp_previous = previous;
    previous = current;
    current = (tmp_previous + current) % m;
    // A Pisano Period starts with 01
    if (previous == 0 && current == 1) return i + 1;
  }
  return 0;  // Just to avoid compiler warning, this line should never be
             // reached
}

long long get_fibonacci_huge_fast(long long n, long long m) {
  long long pisano_period_length = get_pisano_period_length(m);
  n = n % pisano_period_length;  // Reduce n using the Pisano period

  long long previous = 0;
  long long current = 1;

  if (n <= 1) return n;

  for (long long i = 0; i < n - 1; ++i) {
    long long tmp_previous = previous;
    previous = current;
    current = (tmp_previous + current) % m;
  }

  return current % m;
}

int main() {
  long long n, m;
  std::cin >> n >> m;
  std::cout << get_fibonacci_huge_fast(n, m) << std::endl;
  return 0;
}