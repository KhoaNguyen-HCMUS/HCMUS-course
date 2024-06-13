#pragma once

template <typename T>
struct Queue_Recur {
  T *items;
  int front;
  int rear;
  unsigned int count;
  unsigned int maxSize;
  void init(unsigned int size);
  void copyItems(const Queue_Recur<T> &q, int index);
  void copyQueue(const Queue_Recur<T> &q);
  void release();

  bool isEmpty();
  void enqueue(T data);
  T dequeue();
  T frontValue();
  void printRecursive(int index);
  void print();
};
#include "recursive_queue.cpp"