#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using std::string;
using std::vector;

void customSort(vector<string>& a) {
  for (size_t i = 1; i < a.size(); i++) {
    string key = a[i];
    int j = i - 1;

    // Di chuyển các phần tử của a[0..i-1], lớn hơn key, lên một vị trí
    // so với vị trí hiện tại của chúng
    while (j >= 0 && a[j] + key < key + a[j]) {
      a[j + 1] = a[j];
      j = j - 1;
    }
    a[j + 1] = key;
  }
}

string largest_number(vector<string> a) {
  customSort(a);
  std::stringstream ret;
  for (size_t i = 0; i < a.size(); i++) {
    ret << a[i];
  }
  string result;
  ret >> result;
  return result;
}

int main() {
  int n;
  std::cin >> n;
  vector<string> a(n);
  for (size_t i = 0; i < a.size(); i++) {
    std::cin >> a[i];
  }
  std::cout << largest_number(a);
}
