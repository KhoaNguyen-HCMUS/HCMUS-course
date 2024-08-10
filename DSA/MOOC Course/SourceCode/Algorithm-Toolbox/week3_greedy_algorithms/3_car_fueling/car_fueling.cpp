#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::max;
using std::vector;

int compute_min_refills(int d, int m, vector<int>& stops) {
  stops.insert(stops.begin(), 0);  // Add start point
  stops.push_back(d);              // Add destination as the last stop
  int num_refills = 0, current_position = 0;

  for (int i = 1; i < stops.size(); ++i) {
    if (stops[i] - stops[i - 1] > m) {
      // Cannot reach the next stop
      return -1;
    }

    if (stops[i] - current_position > m) {
      // Need to refill at the previous stop
      current_position = stops[i - 1];
      ++num_refills;
    }
  }

  return num_refills;
}

int main() {
  int d = 0;
  cin >> d;
  int m = 0;
  cin >> m;
  int n = 0;
  cin >> n;

  vector<int> stops(n);
  for (size_t i = 0; i < n; ++i) cin >> stops.at(i);

  cout << compute_min_refills(d, m, stops) << "\n";

  return 0;
}
