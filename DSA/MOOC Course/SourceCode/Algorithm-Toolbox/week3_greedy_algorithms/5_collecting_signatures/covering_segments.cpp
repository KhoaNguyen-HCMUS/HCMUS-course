#include <algorithm>
#include <climits>
#include <iostream>
#include <vector>

using std::vector;

struct Segment {
  int left, right;
};

static bool cmp(struct Segment a, struct Segment b) {
  return a.right < b.right;
}

vector<int> optimal_points(vector<Segment> &segments) {
  sort(segments.begin(), segments.end(), cmp);
  vector<int> selected_points;
  int last_right = segments[0].right;
  selected_points.push_back(last_right);
  int n = segments.size();
  for (int i = 1; i < n; ++i) {
    if (segments[i].left > last_right) {
      last_right = segments[i].right;
      selected_points.push_back(last_right);
    }
  }
  return selected_points;
}

int main() {
  int n;
  std::cin >> n;
  vector<Segment> segments(n);
  for (size_t i = 0; i < segments.size(); ++i) {
    std::cin >> segments[i].left >> segments[i].right;
  }
  vector<int> points = optimal_points(segments);
  std::cout << points.size() << "\n";
  for (size_t i = 0; i < points.size(); ++i) {
    std::cout << points[i] << " ";
  }
}
