#pragma once

template <typename T>
struct Stack_Recur {
  T* items;
  int top;
  unsigned int size;
  void init(unsigned int size);
  void copyStack(const Stack_Recur<T>& source);
  void copyStackRecursively(const Stack_Recur<T>& source, int currentIndex);
  void release();
  bool isEmpty();
  void push(T data);
  T pop();
  T topValue();
  void printRecursively(int currentIndex);
  void print();
};
#include "recursive_stack.cpp"