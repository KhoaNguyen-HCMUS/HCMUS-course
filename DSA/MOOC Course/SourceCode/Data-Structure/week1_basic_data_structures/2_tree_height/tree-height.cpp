#include <algorithm>
#include <iostream>
#include <vector>

struct Node {
  std::vector<Node*> children;
};

int calculateHeight(Node* node) {
  if (node->children.empty()) {
    return 1;  // Leaf node
  }
  int maxChildHeight = 0;
  for (Node* child : node->children) {
    maxChildHeight = std::max(maxChildHeight, calculateHeight(child));
  }
  return maxChildHeight + 1;  // Add one for the current node
}

Node* buildTree(const std::vector<int>& parent) {
  int n = parent.size();
  std::vector<Node*> nodes(n);
  for (int i = 0; i < n; ++i) {
    nodes[i] = new Node();
  }
  Node* root = nullptr;
  for (int i = 0; i < n; ++i) {
    if (parent[i] == -1) {
      root = nodes[i];  // Found the root
    } else {
      nodes[parent[i]]->children.push_back(nodes[i]);
    }
  }
  return root;
}

int main() {
  int n;
  std::cin >> n;
  std::vector<int> parent(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> parent[i];
  }
  Node* root = buildTree(parent);
  std::cout << calculateHeight(root) << std::endl;
  return 0;
}