#pragma once
template <typename T>
struct Queue {
  struct Node {
    T data;
    Node* next;
  };
  Node* front;
  Node* rear;
  void init();
  void copyQueue(Queue<T>& src);
  void release();
  bool isEmpty();
  void enqueue(T newItem);
  T dequeue();
  T frontValue();
  void print();
};
#include "queue.cpp"