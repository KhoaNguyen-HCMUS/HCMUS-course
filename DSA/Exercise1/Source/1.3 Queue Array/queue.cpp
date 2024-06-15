#include "queue.h"
using namespace std;
template <typename T>
void Queue<T>::init(unsigned int size) {
  maxSize = size;
  front = -1;
  rear = -1;
  count = 0;
  items = new T[maxSize];
}

template <typename T>
void Queue<T>::copyQueue(const Queue<T> &q) {
  maxSize = q.maxSize;
  front = q.front;
  rear = q.rear;
  count = q.count;
  items = new T[maxSize];
  for (int i = 0; i < maxSize; i++) items[i] = q.items[i];
}

template <typename T>
void Queue<T>::release() {
  front = -1;
  rear = -1;
  count = 0;
  maxSize = 0;
  delete[] items;
  items = nullptr;
}

template <typename T>
bool Queue<T>::isEmpty() {
  return front > rear || count == 0;
}

template <typename T>
void Queue<T>::enqueue(T data) {
  if (count == maxSize) {
    cout << "Queue is full, can't enqueue" << endl;
    return;
  }
  if (front == -1) front = 0;
  rear = (rear + 1) % maxSize;
  items[rear] = data;
  count++;
}

template <typename T>
T Queue<T>::dequeue() {
  if (isEmpty()) {
    cout << "Queue is empty" << endl;
    return T();
  }
  T data = items[front];
  front = (front + 1) % maxSize;
  count--;
  return data;
}

template <typename T>
T Queue<T>::frontValue() {
  return items[front];
}

template <typename T>
void Queue<T>::print() {
  if (isEmpty()) {
    cout << "Queue is empty, can't print." << endl;
    return;
  }
  cout << "Queue: " << endl;
  for (int i = front; i <= rear; i++) cout << items[i] << " ";
  cout << endl;
}