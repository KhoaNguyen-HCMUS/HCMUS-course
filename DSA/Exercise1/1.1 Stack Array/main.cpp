#include <iostream>

#include "recursive_stack.h"
#include "stack.h"
using namespace std;

int main() {
  cout << "1. Stack using loop\n";
  cout << "2. Stack using recursion\n";
  cout << "Enter your choice: ";
  int mode = 0;
  cin >> mode;
  if (mode == 1) {
    Stack<int> St;
    cout << "Enter the size of the stack: ";
    unsigned int size = 0;
    cin >> size;
    St.init(size);

    while (true) {
      cout << "\n----Menu----\n";
      cout << "1. Push\n";
      cout << "2. Pop\n";
      cout << "3. Exit\n";
      cout << "Enter your choice: ";
      int choice;
      cin >> choice;

      switch (choice) {
        case 1: {
          cout << "Enter a number to push: ";
          int num;
          cin >> num;
          St.push(num);
          St.print();
          break;
        }
        case 2: {
          if (!St.isEmpty()) {
            int num = St.pop();
            cout << "Popped " << num << "\n";
            St.print();
          } else {
            cout << "Stack is empty, can't pop.\n";
          }
          break;
        }
        case 3: {
          St.release();
          cout << "Exiting...\n";
          return 0;
        }
        default:
          cout << "Invalid choice. Please enter 1, 2,or 3.\n";
      }
    }
  } else {
    Stack_Recur<int> St;

    cout << "Enter the size of the stack: ";
    unsigned int size = 0;
    cin >> size;
    St.init(size);

    while (true) {
      cout << "\n----Menu----\n";
      cout << "1. Push\n";
      cout << "2. Pop\n";
      cout << "3. Exit\n";
      cout << "Enter your choice: ";
      int choice;
      cin >> choice;

      switch (choice) {
        case 1: {
          cout << "Enter a number to push: ";
          int num;
          cin >> num;
          St.push(num);
          St.print();
          break;
        }
        case 2: {
          if (!St.isEmpty()) {
            int num = St.pop();
            cout << "Popped " << num << "\n";
            St.print();
          } else {
            cout << "Stack is empty, can't pop.\n";
          }
          break;
        }
        case 3: {
          St.release();
          cout << "Exiting...\n";
          return 0;
        }
        default:
          cout << "Invalid choice. Please enter 1, 2,or 3.\n";
      }
    }
  }

  return 0;
}