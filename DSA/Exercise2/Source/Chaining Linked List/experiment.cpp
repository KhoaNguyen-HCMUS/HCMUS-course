#include <time.h>

#include <chrono>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

#include "hash.h"
using namespace std::chrono;
using namespace std;

struct book {
  string key, value;
};

void readData(vector<book>& vectorTable,
              hashTable<string, string>& hashingTable) {
  ifstream file("../books.txt");
  if (!file.is_open()) {
    cerr << "Error opening file" << endl;
    return;
  }

  string line;
  // Skip the first line (header)
  getline(file, line);

  while (getline(file, line)) {
    stringstream ss(line);
    string key;
    string value;

    // Split the line by '|'
    if (getline(ss, key, '|') && getline(ss, value)) {
      hashingTable.add(key, value);
      vectorTable.push_back({key, value});
    }
  }

  file.close();
}

string searchInVector(vector<book>& vectorTable, string key) {
  for (auto& book : vectorTable) {
    if (book.key == key) {
      return book.value;
    }
  }
  return "Not Found";
}

string searchInHashTable(hashTable<string, string>& hashingTable, string key) {
  string* result = hashingTable.searchValue(key);
  return result ? *result : "Not Found";
}

int main() {
  vector<book> vectorTable;
  hashTable<string, string> hashingTable;
  hashingTable.init(300000);
  readData(vectorTable, hashingTable);

  cout << "Data loaded successfully" << endl << endl;

  cout << "--------Chaining by Linked List--------" << endl;
  string startTitle = vectorTable[0].key;
  string middleTitle = vectorTable[vectorTable.size() / 2].key;
  string endTitle = vectorTable[vectorTable.size() - 1].key;
  string notFoundTitle = "Khoa Nguyen 23CLC09";

  cout << "Searching for the first title: " << endl;

  auto start = high_resolution_clock::now();
  cout << "Searching in vector: \t\t" << searchInVector(vectorTable, startTitle)
       << endl;
  auto stop = high_resolution_clock::now();
  auto duration = duration_cast<microseconds>(stop - start);
  cout << "Time taken: \t\t\t" << duration.count() << " microseconds" << endl;

  start = high_resolution_clock::now();
  cout << "Searching in hash table: \t"
       << searchInHashTable(hashingTable, startTitle) << endl;
  stop = high_resolution_clock::now();
  duration = duration_cast<microseconds>(stop - start);
  cout << "Time taken: \t\t\t" << duration.count() << " microseconds" << endl;
  cout << endl;

  cout << "Searching for the middle title: \t" << endl;
  start = high_resolution_clock::now();
  cout << "Searching in vector: \t\t"
       << searchInVector(vectorTable, middleTitle) << endl;
  stop = high_resolution_clock::now();
  duration = duration_cast<microseconds>(stop - start);
  cout << "Time taken: \t\t\t" << duration.count() << " microseconds" << endl;
  start = high_resolution_clock::now();
  cout << "Searching in hash table: \t"
       << searchInHashTable(hashingTable, middleTitle) << endl;
  stop = high_resolution_clock::now();
  duration = duration_cast<microseconds>(stop - start);
  cout << "Time taken: \t\t\t" << duration.count() << " microseconds" << endl;
  cout << endl;

  cout << "Searching for the last title: " << endl;
  start = high_resolution_clock::now();
  cout << "Searching in vector: \t\t" << searchInVector(vectorTable, endTitle)
       << endl;
  stop = high_resolution_clock::now();
  duration = duration_cast<microseconds>(stop - start);
  cout << "Time taken: \t\t\t" << duration.count() << " microseconds" << endl;

  start = high_resolution_clock::now();
  cout << "Searching in hash table: \t"
       << searchInHashTable(hashingTable, endTitle) << endl;
  stop = high_resolution_clock::now();
  duration = duration_cast<microseconds>(stop - start);
  cout << "Time taken: \t\t\t" << duration.count() << " microseconds" << endl;
  cout << endl;

  cout << "Searching title not exist: " << endl;

  start = high_resolution_clock::now();
  cout << "Searching in vector: \t\t"
       << searchInVector(vectorTable, notFoundTitle) << endl;
  stop = high_resolution_clock::now();
  duration = duration_cast<microseconds>(stop - start);
  cout << "Time taken: \t\t\t" << duration.count() << " microseconds" << endl;

  start = high_resolution_clock::now();
  cout << "Searching in hash table: \t"
       << searchInHashTable(hashingTable, notFoundTitle) << endl;
  stop = high_resolution_clock::now();
  duration = duration_cast<microseconds>(stop - start);
  cout << "Time taken: \t\t\t" << duration.count() << " microseconds" << endl;

  hashingTable.release();
  return 0;
}