#include <iostream>
#include <vector>

using std::vector;

int partition3(vector<int> &A) {
  int sum = 0;
  for (int num : A) {
    sum += num;
  }

  if (sum % 3 != 0) {
    return 0;
  }

  int target = sum / 3;
  int n = A.size();
  vector<vector<vector<bool>>> dp(
      n + 1, vector<vector<bool>>(target + 1, vector<bool>(target + 1, false)));
  dp[0][0][0] = true;

  for (int i = 1; i <= n; ++i) {
    for (int j = 0; j <= target; ++j) {
      for (int k = 0; k <= target; ++k) {
        dp[i][j][k] = dp[i - 1][j][k];
        if (j >= A[i - 1]) {
          dp[i][j][k] = dp[i][j][k] || dp[i - 1][j - A[i - 1]][k];
        }
        if (k >= A[i - 1]) {
          dp[i][j][k] = dp[i][j][k] || dp[i - 1][j][k - A[i - 1]];
        }
      }
    }
  }

  return dp[n][target][target] ? 1 : 0;
}

int main() {
  int n;
  std::cin >> n;
  vector<int> A(n);
  for (size_t i = 0; i < A.size(); ++i) {
    std::cin >> A[i];
  }
  std::cout << partition3(A) << '\n';
}