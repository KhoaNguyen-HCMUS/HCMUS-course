#include "stack.h"

#include <iostream>
using namespace std;

template <typename T>
void Stack<T>::init(unsigned int newSize) {
  size = newSize;
  items = new T[size];
  top = -1;
}

template <typename T>
void Stack<T>::copyStack(const Stack<T>& source) {
  size = source.size;
  items = new T[size];
  top = source.top;
  for (int i = 0; i <= top; i++) {
    items[i] = source.items[i];
  }
}

template <typename T>
void Stack<T>::release() {
  size = 0;
  top = -1;
  delete[] items;
}

template <typename T>
bool Stack<T>::isEmpty() {
  return top == -1;
}

template <typename T>
void Stack<T>::push(T data) {
  if (top + 1 == size) {
    cout << "Stack is full. Can't push." << endl;
    return;
  }
  top++;
  items[top] = data;
}

template <typename T>
T Stack<T>::pop() {
  top--;
  return items[top + 1];
}

template <typename T>
T Stack<T>::topValue() {
  return items[top];
}

template <typename T>
void Stack<T>::print() {
  if (isEmpty()) {
    cout << "Stack is empty. Can't print" << endl;
    return;
  }
  cout << "Stack: " << endl;
  for (int i = 0; i <= top; i++) {
    cout << items[i] << " ";
  }
  cout << endl;
}