#include <iomanip>
#include <iostream>
#include <string>

#include "hash.h"
using namespace std;

void displayMenu() {
  cout << endl;
  cout << "Menu hash table using Quadratic Probing" << endl;
  cout << "---------------------------------------" << endl;
  cout << "1. Add a key-value" << endl;
  cout << "2. Search for a value" << endl;
  cout << "3. Remove a key" << endl;
  cout << "4. Exit" << endl;
}

int main() {
  hashTable<string, int> table;
  int hashSize = 0;
  cout << "Enter hash table size: ";
  cin >> hashSize;
  table.init(hashSize);

  int choice = 0;
  string key = "";
  int value = 0;
  while (true) {
    displayMenu();
    cout << "Enter your choice: ";
    cin >> choice;
    int* result = nullptr;
    switch (choice) {
      case 1:
        cout << "Enter key: ";
        cin >> key;
        cout << "Enter value: ";
        cin >> value;
        table.add(key, value);
        table.display();
        break;

      case 2:
        cout << "Enter key: ";
        cin >> key;
        result = table.searchValue(key);
        if (result == NULL) {
          cout << "Key not found" << endl;
        } else {
          cout << "Value: " << *result << endl;
        }
        table.display();
        break;

      case 3:
        cout << "Enter key: ";
        cin >> key;
        table.removeKey(key);
        table.display();
        break;

      case 4:
        cout << "Exiting..." << endl;
        table.release();
        return 0;
      default:
        cout << "Invalid choice" << endl;
    }
  }
  return 0;
}
