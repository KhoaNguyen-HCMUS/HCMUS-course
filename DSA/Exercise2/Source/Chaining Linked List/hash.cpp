#include "hash.h"

template <typename K, typename V>
void hashTable<K, V>::init(unsigned int hashSize) {
  capacity = hashSize;
  table = new hashNode*[capacity];
  for (int i = 0; i < capacity; i++) {
    table[i] = nullptr;
  }
}

template <typename K, typename V>
void hashTable<K, V>::release() {
  for (int i = 0; i < capacity; ++i) {
    hashNode* entry = table[i];
    while (entry != nullptr) {
      hashNode* prev = entry;
      entry = entry->next;
      delete prev;
    }
    table[i] = nullptr;
  }
  delete[] table;
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
  hashNode* newNode = new hashNode(key, value, nullptr);

  if (table[hashIndex] == nullptr) {
    table[hashIndex] = newNode;
  } else {
    hashNode* current = table[hashIndex];
    while (current != nullptr) {
      if (current->key == key) {
        current->value = value;
        delete newNode;
        return;
      }
      if (current->next == nullptr) {
        break;
      }
      current = current->next;
    }
    current->next = newNode;
  }
}

template <typename K, typename V>
V* hashTable<K, V>::searchValue(K key) {
  unsigned int index = hashFunction(key);
  hashNode* current = table[index];
  while (current != nullptr) {
    if (current->key == key) {
      return &current->value;
    }
    current = current->next;
  }
  return nullptr;
}

template <typename K, typename V>
void hashTable<K, V>::removeKey(K key) {
  unsigned int hashIndex = hashFunction(key);
  hashNode* entry = table[hashIndex];
  hashNode* prev = nullptr;
  while (entry != nullptr && entry->key != key) {
    prev = entry;
    entry = entry->next;
  }
  if (entry == nullptr) {
    cout << "Key not found" << endl;
    return;  // Key not found
  }
  if (prev == nullptr) {
    table[hashIndex] = entry->next;
  } else {
    prev->next = entry->next;
  }
  delete entry;
}

template <typename K, typename V>
void hashTable<K, V>::display() {
  cout << "Hash table:" << endl;
  cout << left << setw(10) << "Bucket"
       << "[Key,Value]" << endl;
  cout << "----------------------------------------" << endl;
  for (int i = 0; i < capacity; i++) {
    cout << left << setw(10) << i;
    hashNode* entry = table[i];
    if (entry == nullptr) {
      cout << endl;
    } else {
      while (entry != nullptr) {
        cout << "[" << entry->key << "," << entry->value << "]";
        entry = entry->next;
        if (entry != nullptr) {
          cout << " -> ";
        }
      }
      cout << endl;
    }
  }
}