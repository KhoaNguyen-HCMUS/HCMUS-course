#pragma once
#include <string>
#include <vector>
using namespace std;

template <typename K, typename V>

struct hashTable {
  struct hashNode {
    K key;
    V value;
    hashNode* next;
    // Constructor to initialize hashNode
    hashNode(const K& k, const V& v, hashNode* n) : key(k), value(v), next(n) {}
  };
  int capacity;
  hashNode** table;

 public:
  void init(unsigned int hashSize);
  void release();
  unsigned int hashFunction(int key);
  unsigned int hashFunction(string key);
  void add(K key, V value);
  V* searchValue(K Key);
  void removeKey(K Key);
  void display();
};

#include "hash.cpp"