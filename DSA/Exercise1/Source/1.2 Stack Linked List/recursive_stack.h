#pragma once

template <typename T>
struct Stack_Recur {
  struct Node {
    T data;
    Node* next;
    Node(T data, Node* next = nullptr) : data(data), next(next) {}
  };
  Node* top;
  void init();
  void copyStack(Stack_Recur<T>& original);
  void copyStackRecursive(Node* originalNode, Node*& thisNode);

  void release();
  void releaseRecursively(Node*& top);

  bool isEmpty();
  void push(T data);
  T pop();
  T topValue();

  void print();
  void printRecursively(Node* node);
};

#include "recursive_stack.cpp"
