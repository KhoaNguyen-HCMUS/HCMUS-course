#include <algorithm>
#include <iostream>
#include <vector>

using std::vector;

long long max_dot_product(vector<int> a, vector<int> b, int n) {
  std::sort(a.begin(), a.end());
  std::sort(b.begin(), b.end());
  long long result = 0;
  for (int i = 0; i < a.size(); i++) {
    long long temp = (long long)a[i] * b[i];
    result += temp;
  }
  return result;
}

int main() {
  size_t n;
  std::cin >> n;
  vector<int> a(n), b(n);
  for (size_t i = 0; i < n; i++) {
    std::cin >> a[i];
  }
  for (size_t i = 0; i < n; i++) {
    std::cin >> b[i];
  }
  std::cout << max_dot_product(a, b, n) << std::endl;
}
