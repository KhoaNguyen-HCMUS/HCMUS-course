#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class DisjointSets {
 public:
  vector<int> parent, rank, size;
  int max_table_size;

  DisjointSets(int n, const vector<int>& sizes) {
    parent.resize(n);
    rank.resize(n, 0);
    size = sizes;
    max_table_size = *max_element(size.begin(), size.end());
    for (int i = 0; i < n; ++i) {
      parent[i] = i;
    }
  }

  int getParent(int table) {
    if (table != parent[table]) {
      parent[table] = getParent(parent[table]);  // Path compression
    }
    return parent[table];
  }

  void merge(int destination, int source) {
    int realDestination = getParent(destination);
    int realSource = getParent(source);
    if (realDestination != realSource) {
      // Union by rank heuristic
      if (rank[realDestination] > rank[realSource]) {
        parent[realSource] = realDestination;
        size[realDestination] += size[realSource];
        size[realSource] = 0;
      } else {
        parent[realDestination] = realSource;
        size[realSource] += size[realDestination];
        size[realDestination] = 0;
        if (rank[realDestination] == rank[realSource]) {
          rank[realSource]++;
        }
      }
      // Update max_table_size
      max_table_size =
          max(max_table_size, max(size[realDestination], size[realSource]));
    }
  }
};

int main() {
  int n, m;
  cin >> n >> m;
  vector<int> sizes(n);
  for (int i = 0; i < n; ++i) {
    cin >> sizes[i];
  }
  DisjointSets tables(n, sizes);
  for (int i = 0; i < m; ++i) {
    int destination, source;
    cin >> destination >> source;
    tables.merge(destination - 1, source - 1);
    cout << tables.max_table_size << endl;
  }
  return 0;
}