#pragma once
#include <string>
#include <vector>
using namespace std;

template <typename K, typename V>

struct hashTable {
  struct hashNode {
    K key;
    V value;
    hashNode* left;
    hashNode* right;
    int height;
    hashNode(K k, V v)
        : key(k), value(v), left(nullptr), right(nullptr), height(1) {}
  };
  int capacity;
  vector<hashNode*> table;

 public:
  void init(unsigned int hashSize);
  void release();
  unsigned int hashFunction(int key);
  unsigned int hashFunction(string key);
  void add(K key, V value);
  V* searchValue(K Key);
  void removeKey(K Key);
  void display();

  int height(hashNode* node);
  int max(int a, int b);
  int getBalance(hashNode* node);
  hashNode* rightRotate(hashNode* y);
  hashNode* leftRotate(hashNode* x);
  hashNode* insertNode(hashNode* node, K key, V value);
  hashNode* newNode(K key, V value);
  void deleteTree(hashNode* node);
  hashNode* minValueNode(hashNode* node);
  hashNode* deleteNode(hashNode* node, K key);
  hashNode* searchNode(hashNode* node, K key);
  void displayTree(hashNode* node);  // In - order traversal
};

#include "hash.cpp"