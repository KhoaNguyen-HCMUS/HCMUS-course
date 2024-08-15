#pragma once
#include <string>
#include <vector>
using namespace std;

template <typename K, typename V>
struct hashTable {
  struct hashNode {
    K key;
    V value;
  };
  int capacity;
  vector<hashNode*> table;

  void init(unsigned int hashSize);
  void release();
  unsigned int hashFunction(int key);
  unsigned int hashFunction(string key);
  void rehash();

  void add(K key, V value);
  V* searchValue(K Key);
  void removeKey(K Key);
  void display();
};

#include "hash.cpp"