#include <algorithm>
#include <cassert>
#include <iostream>
#include <string>
#include <vector>

using std::max;
using std::min;
using std::string;
using std::vector;

long long eval(long long a, long long b, char op) {
  if (op == '*') {
    return a * b;
  } else if (op == '+') {
    return a + b;
  } else if (op == '-') {
    return a - b;
  } else {
    assert(0);
  }
}

void parse_expression(const string &exp, vector<long long> &digits,
                      vector<char> &ops) {
  for (size_t i = 0; i < exp.size(); ++i) {
    if (i % 2 == 0) {
      digits.push_back(exp[i] - '0');
    } else {
      ops.push_back(exp[i]);
    }
  }
}

long long get_maximum_value(const string &exp) {
  vector<long long> digits;
  vector<char> ops;
  parse_expression(exp, digits, ops);

  int n = digits.size();
  vector<vector<long long>> min_values(n, vector<long long>(n, 0));
  vector<vector<long long>> max_values(n, vector<long long>(n, 0));

  for (int i = 0; i < n; ++i) {
    min_values[i][i] = digits[i];
    max_values[i][i] = digits[i];
  }

  for (int s = 1; s < n; ++s) {
    for (int i = 0; i < n - s; ++i) {
      int j = i + s;
      long long min_val = LLONG_MAX;
      long long max_val = LLONG_MIN;
      for (int k = i; k < j; ++k) {
        long long a = eval(min_values[i][k], min_values[k + 1][j], ops[k]);
        long long b = eval(min_values[i][k], max_values[k + 1][j], ops[k]);
        long long c = eval(max_values[i][k], min_values[k + 1][j], ops[k]);
        long long d = eval(max_values[i][k], max_values[k + 1][j], ops[k]);
        min_val = min({min_val, a, b, c, d});
        max_val = max({max_val, a, b, c, d});
      }
      min_values[i][j] = min_val;
      max_values[i][j] = max_val;
    }
  }

  return max_values[0][n - 1];
}

int main() {
  string s;
  std::cin >> s;
  std::cout << get_maximum_value(s) << '\n';
}