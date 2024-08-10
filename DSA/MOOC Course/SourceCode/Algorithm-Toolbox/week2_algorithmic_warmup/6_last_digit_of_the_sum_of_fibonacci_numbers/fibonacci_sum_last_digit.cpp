#include <iostream>
#include <vector>

const int MOD = 10;  // We only need the last digit

// Function to multiply two matrices
void multiply(std::vector<std::vector<long long>>& a,
              std::vector<std::vector<long long>>& b) {
  std::vector<std::vector<long long>> result(2, std::vector<long long>(2));
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      result[i][j] = 0;
      for (int k = 0; k < 2; k++) {
        result[i][j] = (result[i][j] + a[i][k] * b[k][j]) % MOD;
      }
    }
  }
  a = result;
}

// Function to raise the matrix to the power of n
void power(std::vector<std::vector<long long>>& matrix, long long n) {
  if (n <= 1) return;

  power(matrix, n / 2);
  multiply(matrix, matrix);

  if (n % 2 != 0) {
    std::vector<std::vector<long long>> F = {{1, 1}, {1, 0}};
    multiply(matrix, F);
  }
}

// Fast calculation of Fibonacci numbers using matrix exponentiation
int fibonacci_fast(long long n) {
  if (n == 0) return 0;
  std::vector<std::vector<long long>> F = {{1, 1}, {1, 0}};
  power(F, n - 1);
  return F[0][0];
}

int fibonacci_sum_fast(long long n) {
  // The sum of the first n Fibonacci numbers is F(n+2) - 1
  long long last_digit_of_sum = fibonacci_fast(n + 2) - 1;
  if (last_digit_of_sum == -1)  // Adjust if the result is -1
    last_digit_of_sum = 9;
  return last_digit_of_sum;
}

int main() {
  long long n;
  std::cin >> n;
  std::cout << fibonacci_sum_fast(n) << std::endl;
  return 0;
}