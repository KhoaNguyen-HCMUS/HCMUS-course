#include "hash.h"

template <typename K, typename V>

void hashTable<K, V>::init(unsigned int hashSize) {
  capacity = hashSize;
  table = vector<hashNode*>(capacity, NULL);
}

template <typename K, typename V>
void hashTable<K, V>::release() {
  for (int i = 0; i < capacity; i++) {
    if (table[i] != NULL) {
      delete table[i];
      table[i] = NULL;
    }
  }
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
  unsigned int index = hashFunction(key);
  unsigned int startIndex = index;

  while (table[index] != NULL) {
    if (table[index]->key == key) {
      table[index]->value = value;
      return;
    }
    index = (index + 1) % capacity;
    if (index == startIndex) {
      cout << "Table is full, cannot add new key" << endl;
      return;
    }
  }

  table[index] = new hashNode{key, value};
}

template <typename K, typename V>
V* hashTable<K, V>::searchValue(K key) {
  unsigned int index = hashFunction(key);
  unsigned int startIndex = index;
  while (table[index] != NULL && table[index]->key != key) {
    index = (index + 1) % capacity;
    if (index == startIndex) {
      return NULL;
    }
  }
  if (table[index] == NULL) {
    return NULL;
  }
  return &table[index]->value;
}

template <typename K, typename V>
void hashTable<K, V>::removeKey(K key) {
  unsigned int index = hashFunction(key);
  unsigned int startIndex = index;
  while (table[index] != NULL && table[index]->key != key) {
    index = (index + 1) % capacity;
    if (index == startIndex) {
      cout << "Key " << key << " not found" << endl;
      return;
    }
  }
  if (table[index] == NULL) {
    cout << "Key " << key << " not found" << endl;
    return;
  }
  delete table[index];
  table[index] = NULL;
}

template <typename K, typename V>
void hashTable<K, V>::display() {
  cout << "+-------+----------------+----------------+" << endl;
  cout << "| Index |      Key       |      Value     |" << endl;
  cout << "+-------+----------------+----------------+" << endl;

  for (unsigned int i = 0; i < capacity; ++i) {
    if (table[i] != NULL) {
      cout << "| " << setw(5) << i << " | " << setw(14) << table[i]->key
           << " | " << setw(14) << table[i]->value << " |" << endl;
      cout << "+-------+----------------+----------------+" << endl;
    }
  }
}