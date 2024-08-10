#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>

using namespace std;

struct Node {
  int key;
  int left;
  int right;

  Node() : key(0), left(-1), right(-1) {}
  Node(int key_, int left_, int right_)
      : key(key_), left(left_), right(right_) {}
};

bool isBSTUtil(const vector<Node>& tree, int node_index, int min, int max) {
  if (node_index == -1) return true;

  const Node& node = tree[node_index];
  if (node.key < min || node.key > max) return false;

  return isBSTUtil(tree, node.left, min, node.key - 1) &&
         isBSTUtil(tree, node.right, node.key + 1, max);
}

bool IsBinarySearchTree(const vector<Node>& tree) {
  if (tree.empty()) return true;
  return isBSTUtil(tree, 0, numeric_limits<int>::min(),
                   numeric_limits<int>::max());
}

int main() {
  int nodes;
  cin >> nodes;
  vector<Node> tree;
  for (int i = 0; i < nodes; ++i) {
    int key, left, right;
    cin >> key >> left >> right;
    tree.push_back(Node(key, left, right));
  }
  if (IsBinarySearchTree(tree)) {
    cout << "CORRECT" << endl;
  } else {
    cout << "INCORRECT" << endl;
  }
  return 0;
}
