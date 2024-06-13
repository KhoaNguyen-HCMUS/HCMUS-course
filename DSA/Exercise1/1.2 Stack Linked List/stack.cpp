#include "stack.h"

#include <iostream>
using namespace std;

template <typename T>
void Stack<T>::init() {
  top = nullptr;
}

template <typename T>
void Stack<T>::copyStack(const Stack<T>& original) {
  top = nullptr;
  Node* temp = original.top;
  while (temp) {
    push(temp->data);
    temp = temp->next;
  }
}

template <typename T>
void Stack<T>::release() {
  if (!top) {
    cout << "Stack is empty!" << endl;
    return;
  }
  while (top) {
    Node* temp = top;
    top = top->next;
    delete temp;
  }
}

template <typename T>
bool Stack<T>::isEmpty() {
  return (top == nullptr);
}

template <typename T>
void Stack<T>::push(T data) {
  Node* newNode = new Node{data, nullptr};
  newNode->data = data;
  newNode->next = top;
  top = newNode;
}

template <typename T>
T Stack<T>::topValue() {
  if (!top) {
    cout << "Stack is empty. Can't get top value" << endl;
    return T();
  }
  Node* temp = top;
  while (temp->next) {
    temp = temp->next;
  }
  return temp->data;
}

template <typename T>
T Stack<T>::pop() {
  Node* temp = top;
  T res = temp->data;
  top = top->next;
  delete temp;
  return res;
}

template <typename T>
void Stack<T>::print() {
  if (isEmpty) {
    cout << "Stack is empty. Can't print" << endl;
    return;
  }
  cout << "Stack: ";
  printReversed(*this);
}

template <typename T>
void Stack<T>::printReversed(const Stack<T>& original) {
  Stack<T> temp;
  temp.copyStack(original);
  while (!temp.isEmpty()) {
    cout << temp.pop() << " ";
  }
  cout << endl;
}