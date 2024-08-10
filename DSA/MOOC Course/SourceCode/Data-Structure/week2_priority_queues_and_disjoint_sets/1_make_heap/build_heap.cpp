#include <algorithm>
#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::make_pair;
using std::pair;
using std::swap;
using std::vector;

class HeapBuilder {
 private:
  vector<int> data_;
  vector<pair<int, int> > swaps_;

  void WriteResponse() const {
    cout << swaps_.size() << "\n";
    for (int i = 0; i < swaps_.size(); ++i) {
      cout << swaps_[i].first << " " << swaps_[i].second << "\n";
    }
  }

  void ReadData() {
    int n;
    cin >> n;
    data_.resize(n);
    for (int i = 0; i < n; ++i) cin >> data_[i];
  }
  void SiftDown(int i) {
    int minIndex = i;
    int leftChild = 2 * i + 1;
    if (leftChild < data_.size() && data_[leftChild] < data_[minIndex]) {
      minIndex = leftChild;
    }
    int rightChild = 2 * i + 2;
    if (rightChild < data_.size() && data_[rightChild] < data_[minIndex]) {
      minIndex = rightChild;
    }
    if (i != minIndex) {
      std::swap(data_[i], data_[minIndex]);
      swaps_.push_back(std::make_pair(i, minIndex));
      SiftDown(minIndex);
    }
  }
  void GenerateSwaps() {
    swaps_.clear();
    for (int i = data_.size() / 2; i >= 0; i--) {
      SiftDown(i);
    }
  }

 public:
  void Solve() {
    ReadData();
    GenerateSwaps();
    WriteResponse();
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  HeapBuilder heap_builder;
  heap_builder.Solve();
  return 0;
}
