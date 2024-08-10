#include <iostream>
#include <vector>

using std::vector;

int optimal_weight(int W, const vector<int> &w) {
  int n = w.size();
  vector<vector<int>> dp(n + 1, vector<int>(W + 1, 0));

  for (int i = 1; i <= n; ++i) {
    for (int weight = 1; weight <= W; ++weight) {
      dp[i][weight] = dp[i - 1][weight];
      if (w[i - 1] <= weight) {
        int val = dp[i - 1][weight - w[i - 1]] + w[i - 1];
        if (dp[i][weight] < val) {
          dp[i][weight] = val;
        }
      }
    }
  }

  return dp[n][W];
}

int main() {
  int n, W;
  std::cin >> W >> n;
  vector<int> w(n);
  for (int i = 0; i < n; i++) {
    std::cin >> w[i];
  }
  std::cout << optimal_weight(W, w) << '\n';
}