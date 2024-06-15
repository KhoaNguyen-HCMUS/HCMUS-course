#include "recursive_stack.h"

#include <iostream>
using namespace std;

template <typename T>
void Stack_Recur<T>::init() {
  top = nullptr;
}

template <typename T>
void Stack_Recur<T>::copyStack(Stack_Recur<T>& original) {
  if (original.top == nullptr) {
    top = nullptr;
  } else {
    top = new Node(original.top->data, nullptr);
    copyStackRecursive(original.top->next, top->next);
  }
}

template <typename T>
void Stack_Recur<T>::copyStackRecursive(Node* originalNode, Node*& thisNode) {
  if (originalNode == nullptr) {
    thisNode = nullptr;
  } else {
    thisNode = new Node(originalNode->data, nullptr);
    copyStackRecursive(originalNode->next, thisNode->next);
  }
}

template <typename T>
void Stack_Recur<T>::release() {
  releaseRecursively(top);
}

template <typename T>
void Stack_Recur<T>::releaseRecursively(Node*& top) {
  if (top == nullptr) {
    return;
  }
  releaseRecursively(top->next);
  delete top;
  top = nullptr;
}

template <typename T>
bool Stack_Recur<T>::isEmpty() {
  return (top == nullptr);
}

template <typename T>
void Stack_Recur<T>::push(T data) {
  Node* newNode = new Node{data, nullptr};
  newNode->data = data;
  newNode->next = top;
  top = newNode;
}

template <typename T>
T Stack_Recur<T>::topValue() {
  if (!top) {
    cout << "Stack is empty. Can't get top value" << endl;
    return T();
  }
  return top->data;
}

template <typename T>
T Stack_Recur<T>::pop() {
  Node* temp = top;
  T res = temp->data;
  top = top->next;
  delete temp;
  return res;
}

template <typename T>
void Stack_Recur<T>::printRecursively(Node* node) {
  if (node == nullptr) {
    return;
  }
  printRecursively(node->next);
  cout << node->data << " ";
}

template <typename T>
void Stack_Recur<T>::print() {
  if (isEmpty()) {
    cout << "Stack is empty. Can't print" << endl;
    return;
  }
  printRecursively(top);
  cout << endl;
}
