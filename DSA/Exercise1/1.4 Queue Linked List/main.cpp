#include <iostream>

#include "queue.h"
#include "recursive_queue.h"
using namespace std;

int main() {
  cout << "1. Queue using loop\n";
  cout << "2. Queue using recursion\n";
  cout << "Enter your choice: ";
  int mode = 0;
  cin >> mode;
  if (mode == 1) {
    Queue<int> Q;
    Q.init();
    while (true) {
      cout << "\n-----Menu-----\n";
      cout << "1. Enqueue\n";
      cout << "2. Dequeue\n";
      cout << "3. Exit\n";
      cout << "Enter your choice: ";
      int choice;
      cin >> choice;

      switch (choice) {
        case 1: {
          cout << "Enter a number to enqueue: ";
          int num;
          cin >> num;
          Q.enqueue(num);
          Q.print();
          break;
        }
        case 2: {
          if (!Q.isEmpty()) {
            int num = Q.dequeue();
            cout << "Dequeued " << num << "\n";
            Q.print();

          } else {
            cout << "Queue is empty, can't dequeue\n";
          }
          break;
        }
        case 3: {
          Q.release();
          cout << "Exiting...\n";
          return 0;
        }
        default:
          cout << "Invalid choice. Please enter 1, 2, or 3.\n";
      }
    }
  } else {
    Queue_Recur<int> Q;
    Q.init();
    while (true) {
      cout << "\n-----Menu-----\n";
      cout << "1. Enqueue\n";
      cout << "2. Dequeue\n";
      cout << "3. Exit\n";
      cout << "Enter your choice: ";
      int choice;
      cin >> choice;

      switch (choice) {
        case 1: {
          cout << "Enter a number to enqueue: ";
          int num;
          cin >> num;
          Q.enqueue(num);
          Q.print();

          break;
        }
        case 2: {
          if (!Q.isEmpty()) {
            int num = Q.dequeue();
            cout << "Dequeued " << num << "\n";
            Q.print();

          } else {
            cout << "Queue is empty, can't dequeue\n";
          }
          break;
        }
        case 3: {
          Q.release();
          cout << "Exiting...\n";
          return 0;
        }
        default:
          cout << "Invalid choice. Please enter 1, 2, or 3.\n";
      }
    }
  }
}