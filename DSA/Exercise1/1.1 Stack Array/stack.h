#pragma once

template <typename T>
struct Stack {
  T* items;
  int top;
  unsigned int size;
  void init(unsigned int newSize);
  void copyStack(const Stack<T>& source);
  void release();

  bool isEmpty();
  void push(T data);
  T pop();
  T topValue();
  void print();
};
#include "stack.cpp"