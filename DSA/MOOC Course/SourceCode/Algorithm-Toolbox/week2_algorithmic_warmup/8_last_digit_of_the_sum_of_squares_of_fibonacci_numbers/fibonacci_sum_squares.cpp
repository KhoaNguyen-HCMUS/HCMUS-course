#include <iostream>

long long fibonacci_fast(int n) {
  if (n <= 1) return n;

  long long previous = 0;
  long long current = 1;

  for (int i = 0; i < n - 1; ++i) {
    long long tmp_previous = previous;
    previous = current;
    current = tmp_previous + current;
    current = current % 10;  // Modulo 10 if only the last digit is needed
  }

  return current;
}

long long fibonacci_sum_squares_fast(long long n) {
  // The Pisano period for modulo 10 is 60
  n = n % 60;
  if (n <= 1) return n;

  long long previous = 0;
  long long current = 1;
  long long sum = 1;  // Base case: F0^2 + F1^2 = 0 + 1 = 1

  for (long long i = 2; i <= n; ++i) {
    long long tmp_previous = previous;
    previous = current;
    current =
        (tmp_previous + current) % 10;  // Only interested in the last digit
    sum = (sum + (current * current) % 10) % 10;  // Sum of squares modulo 10
  }

  return sum;
}
int main() {
  int n;
  std::cin >> n;
  std::cout << fibonacci_sum_squares_fast(n) << '\n';
  return 0;
}