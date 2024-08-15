#include "hash.h"

template <typename K, typename V>
void hashTable<K, V>::init(unsigned int hashSize) {
  capacity = hashSize;
  table.resize(capacity);
  for (int i = 0; i < capacity; i++) {
    table[i] = nullptr;
  }
}

template <typename K, typename V>
void hashTable<K, V>::release() {
  for (int i = 0; i < capacity; i++) {
    if (table[i] != nullptr) {
      delete table[i];
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
void hashTable<K, V>::rehash() {
  unsigned int oldCapacity = capacity;
  capacity *= 2;
  vector<hashNode*> oldTable = table;

  table = vector<hashNode*>(capacity, nullptr);

  for (unsigned int i = 0; i < oldCapacity; ++i) {
    if (oldTable[i] != nullptr) {
      add(oldTable[i]->key, oldTable[i]->value);
      delete oldTable[i];
    }
  }
}

template <typename K, typename V>
void hashTable<K, V>::add(K key, V value) {
  unsigned int index = hashFunction(key);
  unsigned int start = index;
  unsigned int i = 0;
  while (table[index] != nullptr) {
    if (table[index]->key == key) {
      table[index]->value = value;
      return;
    }
    i++;
    index = (start + i * i) % capacity;
    if (i == capacity) {
      cout << "Table is full. Rehashing..." << endl;
      rehash();
      add(key, value);
      return;
    }
  }
  table[index] = new hashNode{key, value};
}

template <typename K, typename V>
V* hashTable<K, V>::searchValue(K key) {
  unsigned int index = hashFunction(key);
  unsigned int i = 0;
  unsigned int initialIndex = index;
  while (table[index] != nullptr) {
    if (table[index]->key == key) {
      return &table[index]->value;
    }
    i++;
    index = (initialIndex + i * i) % capacity;
    if (i == capacity) {
      break;  // Prevent infinite loop
    }
  }
  return nullptr;  // Key not found
}

template <typename K, typename V>
void hashTable<K, V>::removeKey(K key) {
  unsigned int index = hashFunction(key);
  unsigned int i = 0;
  unsigned int initialIndex = index;
  while (table[index] != nullptr) {
    if (table[index]->key == key) {
      delete table[index];
      table[index] = nullptr;
      cout << "Key " << key << " removed" << endl;
      return;
    }
    i++;
    index = (initialIndex + i * i) % capacity;
    if (i == capacity) {
      break;  // Prevent infinite loop
    }
  }
  cout << "Key " << key << " not found" << endl;
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