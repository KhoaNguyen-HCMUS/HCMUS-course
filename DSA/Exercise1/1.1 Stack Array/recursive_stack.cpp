#include "recursive_stack.h"

#include <iostream>
using namespace std;

template <typename T>
void Stack_Recur<T>::init(unsigned int newSize) {
  size = newSize;
  items = new T[size];
  top = -1;
}

template <typename T>
void Stack_Recur<T>::copyStackRecursively(const Stack_Recur<T>& source,
                                          int currentIndex) {
  if (currentIndex < 0) {
    // Base case: All elements copied
    return;
  }
  copyStackRecursively(source, currentIndex - 1);
  items[currentIndex] = source.items[currentIndex];
}

template <typename T>
void Stack_Recur<T>::copyStack(const Stack_Recur<T>& source) {
  copyStackRecursively(source, source.top);
}

template <typename T>
void Stack_Recur<T>::release() {
  size = 0;
  top = -1;
  delete[] items;
}

template <typename T>
bool Stack_Recur<T>::isEmpty() {
  return top == -1;
}

template <typename T>
void Stack_Recur<T>::push(T data) {
  if (top + 1 == size) {
    cout << "Stack is full. Can't push." << endl;
    return;
  }
  top++;
  items[top] = data;
}

template <typename T>
T Stack_Recur<T>::pop() {
  top--;
  return items[top + 1];
}

template <typename T>
T Stack_Recur<T>::topValue() {
  return items[top];
}

template <typename T>
void Stack_Recur<T>::printRecursively(int currentIndex) {
  if (currentIndex < 0) {
    cout << endl;  // Base case: All elements printed
    return;
  }
  cout << items[currentIndex] << " ";
  printRecursively(currentIndex - 1);
}

template <typename T>
void Stack_Recur<T>::print() {
  if (isEmpty()) {
    cout << "Stack is empty. Can't print" << endl;
    return;
  }
  cout << "Stack: ";
  printRecursively(top);
}