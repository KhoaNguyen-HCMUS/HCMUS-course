#include <algorithm>  // For std::sort
#include <iostream>
#include <vector>
using namespace std;

struct item {
  int cost;
  int weight;
  double avg;
};

void sortList(vector<item>& list) {
  sort(list.begin(), list.end(),
       [](const item& a, const item& b) { return a.avg > b.avg; });
}

double get_optimal_value(int W, vector<item> list) {
  sortList(list);
  double res = 0.0;
  for (int i = 0; i < list.size(); i++) {
    if (list[i].weight <= W) {  // If the whole item can be added
      res += list[i].cost;      // Add the whole value of the item
      W -= list[i].weight;      // Decrease the capacity
    } else {                    // If only a fraction of the item can be added
      double fraction = (double)W / list[i].weight;
      res += fraction * list[i].cost;  // Add the fraction of the item's value
      W = 0;                           // Knapsack is now full
    }
  }
  return res;
}

int main() {
  int n, W;
  cin >> n >> W;
  vector<item> list(n);
  for (int i = 0; i < n; i++) {
    cin >> list[i].cost >> list[i].weight;
    list[i].avg = (double)list[i].cost / list[i].weight;
  }
  double optimal_value = get_optimal_value(W, list);

  std::cout.precision(10);  // Set precision for floating point output
  std::cout << optimal_value << std::endl;
}