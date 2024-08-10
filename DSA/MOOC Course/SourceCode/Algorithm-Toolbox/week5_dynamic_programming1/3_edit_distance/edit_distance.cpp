#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using std::min;
using std::string;
using std::vector;

int edit_distance(const string &str1, const string &str2) {
  int m = str1.size();
  int n = str2.size();
  vector<vector<int>> dp(m + 1, vector<int>(n + 1));

  for (int i = 0; i <= m; ++i) {
    for (int j = 0; j <= n; ++j) {
      if (i == 0) {
        dp[i][j] = j;  // str1 is empty, insert all characters of str2
      } else if (j == 0) {
        dp[i][j] = i;  // str2 is empty, remove all characters of str1
      } else if (str1[i - 1] == str2[j - 1]) {
        dp[i][j] = dp[i - 1][j - 1];  // characters match, no operation needed
      } else {
        dp[i][j] = min({
            dp[i - 1][j] + 1,     // delete
            dp[i][j - 1] + 1,     // insert
            dp[i - 1][j - 1] + 1  // substitute
        });
      }
    }
  }

  return dp[m][n];
}

int main() {
  string str1;
  string str2;
  std::cin >> str1 >> str2;
  std::cout << edit_distance(str1, str2) << std::endl;
  return 0;
}