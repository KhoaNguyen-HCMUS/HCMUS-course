#pragma once
template <typename T>
struct Queue_Recur {
  struct Node {
    T data;
    Node* next;
  };
  Node* front;
  Node* rear;
  void init();
  void releaseRecursively(Node* node);
  void release();
  Node* copyQueueRecursively(Node* node);
  void copyQueue(Queue_Recur<T>& source);
  bool isEmpty();
  void enqueue(T newItem);
  T dequeue();
  T frontValue();

  void printRecursively(Node* node);
  void print();
};
#include "recursive_queue.cpp"