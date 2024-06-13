#pragma once

template <typename T>
struct Stack {
  struct Node {
    T data;
    Node* next;
  };
  Node* top;
  void init();
  void copyStack(const Stack<T>& original);
  void release();

  bool isEmpty();
  void push(T data);
  T pop();
  T topValue();

  void print();
  void printReversed(const Stack<T>& original);
};

#include "stack.cpp"
