#include "hash.h"

#include <iostream>

template <typename K, typename V>
void hashTable<K, V>::init(unsigned int hashSize) {
  capacity = hashSize;
  table.resize(capacity);
  for (int i = 0; i < capacity; ++i) {
    table[i] = nullptr;
  }
}

template <typename K, typename V>
void hashTable<K, V>::release() {
  for (auto& node : table) {
    deleteTree(node);
  }
  table.clear();
}

template <typename K, typename V>
unsigned int hashTable<K, V>::hashFunction(int key) {
  return key % capacity;
}

template <typename K, typename V>
unsigned int hashTable<K, V>::hashFunction(string key) {
  const int p = 31;
  const int m = 1e9 + 9;
  unsigned long long hash = 0;
  unsigned long long p_pow = 1;

  for (char c : key) {
    hash = (hash + (c * p_pow) % m) % m;
    p_pow = (p_pow * p) % m;
  }

  return hash % capacity;
}

template <typename K, typename V>
void hashTable<K, V>::add(K key, V value) {
  unsigned int hashIndex = hashFunction(key);
  table[hashIndex] = insertNode(table[hashIndex], key, value);
}

template <typename K, typename V>
V* hashTable<K, V>::searchValue(K key) {
  unsigned int hashIndex = hashFunction(key);
  hashNode* node = searchNode(table[hashIndex], key);
  return node ? &node->value : nullptr;
}

template <typename K, typename V>
void hashTable<K, V>::removeKey(K key) {
  unsigned int hashIndex = hashFunction(key);
  table[hashIndex] = deleteNode(table[hashIndex], key);
}

template <typename K, typename V>
void hashTable<K, V>::display() {
  cout << "Hash table:" << endl;
  cout << left << setw(10) << "Bucket"
       << "[Key,Value]" << endl;
  cout << "----------------------------------------" << endl;
  for (int i = 0; i < capacity; ++i) {
    cout << left << setw(10) << i;
    if (table[i] != nullptr) displayTree(table[i]);
    cout << endl;
  }
}

template <typename K, typename V>
int hashTable<K, V>::height(hashNode* node) {
  return node ? node->height : 0;
}

template <typename K, typename V>
int hashTable<K, V>::max(int a, int b) {
  return (a > b) ? a : b;
}

template <typename K, typename V>
int hashTable<K, V>::getBalance(hashNode* node) {
  return node ? height(node->left) - height(node->right) : 0;
}

template <typename K, typename V>
typename hashTable<K, V>::hashNode* hashTable<K, V>::rightRotate(hashNode* y) {
  hashNode* x = y->left;
  hashNode* T2 = x->right;
  x->right = y;
  y->left = T2;
  y->height = max(height(y->left), height(y->right)) + 1;
  x->height = max(height(x->left), height(x->right)) + 1;
  return x;
}

template <typename K, typename V>
typename hashTable<K, V>::hashNode* hashTable<K, V>::leftRotate(hashNode* x) {
  hashNode* y = x->right;
  hashNode* T2 = y->left;
  y->left = x;
  x->right = T2;
  x->height = max(height(x->left), height(x->right)) + 1;
  y->height = max(height(y->left), height(y->right)) + 1;
  return y;
}

template <typename K, typename V>
typename hashTable<K, V>::hashNode* hashTable<K, V>::insertNode(hashNode* node,
                                                                K key,
                                                                V value) {
  if (!node) return new hashNode(key, value);
  if (key < node->key)
    node->left = insertNode(node->left, key, value);
  else if (key > node->key)
    node->right = insertNode(node->right, key, value);
  else {
    node->value = value;
    return node;
  }

  node->height = 1 + max(height(node->left), height(node->right));
  int balance = getBalance(node);

  if (balance > 1 && key < node->left->key) return rightRotate(node);
  if (balance < -1 && key > node->right->key) return leftRotate(node);
  if (balance > 1 && key > node->left->key) {
    node->left = leftRotate(node->left);
    return rightRotate(node);
  }
  if (balance < -1 && key < node->right->key) {
    node->right = rightRotate(node->right);
    return leftRotate(node);
  }
  return node;
}
template <typename K, typename V>
typename hashTable<K, V>::hashNode* hashTable<K, V>::newNode(K key, V value) {
  hashNode* node = new hashNode;
  node->key = key;
  node->value = value;
  node->height = 1;
  node->left = node->right = NULL;
  return node;
}

template <typename K, typename V>
void hashTable<K, V>::deleteTree(hashNode* node) {
  if (node == nullptr) {
    return;
  }
  deleteTree(node->left);
  deleteTree(node->right);
  delete node;
}

template <typename K, typename V>
typename hashTable<K, V>::hashNode* hashTable<K, V>::minValueNode(
    hashNode* node) {
  hashNode* current = node;
  while (current->left != nullptr) current = current->left;
  return current;
}

template <typename K, typename V>
typename hashTable<K, V>::hashNode* hashTable<K, V>::deleteNode(hashNode* root,
                                                                K key) {
  if (root == nullptr) {
    cout << "Key not found" << endl;
    return root;
  }
  if (key < root->key)
    root->left = deleteNode(root->left, key);
  else if (key > root->key)
    root->right = deleteNode(root->right, key);
  else {
    if ((root->left == nullptr) || (root->right == nullptr)) {
      hashNode* temp = root->left ? root->left : root->right;
      if (temp == nullptr) {
        temp = root;
        root = nullptr;
      } else
        *root = *temp;
      delete temp;
    } else {
      hashNode* temp = minValueNode(root->right);
      root->key = temp->key;
      root->right = deleteNode(root->right, temp->key);
    }
  }
  if (root == nullptr) return root;
  root->height = 1 + max(height(root->left), height(root->right));
  int balance = getBalance(root);
  if (balance > 1 && getBalance(root->left) >= 0) return rightRotate(root);
  if (balance > 1 && getBalance(root->left) < 0) {
    root->left = leftRotate(root->left);
    return rightRotate(root);
  }
  if (balance < -1 && getBalance(root->right) <= 0) return leftRotate(root);
  if (balance < -1 && getBalance(root->right) > 0) {
    root->right = rightRotate(root->right);
    return leftRotate(root);
  }
  return root;
}

template <typename K, typename V>
typename hashTable<K, V>::hashNode* hashTable<K, V>::searchNode(hashNode* node,
                                                                K key) {
  if (node == nullptr || node->key == key) return node;
  if (key < node->key) return searchNode(node->left, key);
  return searchNode(node->right, key);
}

template <typename K, typename V>
void hashTable<K, V>::displayTree(hashNode* node) {
  if (node == nullptr) return;
  displayTree(node->left);
  cout << '[' << node->key << "," << node->value << "] ";
  displayTree(node->right);
}
