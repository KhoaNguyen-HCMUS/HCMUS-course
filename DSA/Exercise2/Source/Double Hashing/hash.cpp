#include "hash.h"

template <typename K, typename V>
void hashTable<K, V>::init(unsigned int hashSize) {
  capacity = hashSize;
  table = vector<hashNode*>(hashSize, NULL);
}

template <typename K, typename V>
void hashTable<K, V>::release() {
  for (int i = 0; i < capacity; i++) {
    if (table[i] != NULL) {
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
unsigned int hashTable<K, V>::subHashFunction(int key) {
  return 1 + (key % (capacity - 1));
}

template <typename K, typename V>
unsigned int hashTable<K, V>::subHashFunction(string key) {
  return 1 + (hashFunction(key) % (capacity - 1));
}

template <typename K, typename V>
void hashTable<K, V>::rehash() {
  hashTable<K, V> oldTable = *this;
  capacity *= 2;
  table = vector<hashNode*>(capacity, NULL);
  for (int i = 0; i < oldTable.capacity; i++) {
    if (oldTable.table[i] != NULL) {
      add(oldTable.table[i]->key, oldTable.table[i]->value);
    }
  }

  for (int i = 0; i < oldTable.capacity; i++) {
    if (oldTable.table[i] != NULL) {
      delete oldTable.table[i];
    }
  }

  oldTable.table.clear();
}

template <typename K, typename V>
void hashTable<K, V>::add(K key, V value) {
  unsigned int index = hashFunction(key);
  unsigned int initialIndex = index;
  unsigned int i = 0;
  while (table[index] != nullptr) {
    if (table[index]->key == key) {
      table[index]->value = value;
      return;
    }
    i++;
    index = (initialIndex + i * subHashFunction(key)) % capacity;
    if (i == capacity) {
      cout << "Table is full, rehashing..." << endl;
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
    index = (initialIndex + i * subHashFunction(key)) % capacity;
    if (i > capacity) {
      return nullptr;
    }
  }
  return nullptr;
}

template <typename K, typename V>
void hashTable<K, V>::removeKey(K key) {
  unsigned int index = hashFunction(key);
  unsigned int i = 0;
  unsigned int initialIndex = index;
  while (table[index] != NULL) {
    if (table[index]->key == key) {
      delete table[index];
      table[index] = NULL;
      return;
    }
    i++;
    index = (initialIndex + i * subHashFunction(key)) % capacity;
    if (i == capacity) {
      cout << "Key not found" << endl;
      return;
    }
  }
  cout << "Key not found" << endl;
  return;
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