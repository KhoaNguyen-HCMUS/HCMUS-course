#pragma once

template <typename T>
struct Queue {
  T *items;
  int front;
  int rear;
  unsigned int count;
  unsigned int maxSize;
  void init(unsigned int size);
  void copyQueue(const Queue<T> &q);
  void release();

  bool isEmpty();
  void enqueue(T data);
  T dequeue();
  T frontValue();

  void print();
};
#include "queue.cpp"