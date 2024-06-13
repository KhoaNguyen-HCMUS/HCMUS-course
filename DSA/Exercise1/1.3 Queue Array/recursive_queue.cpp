#include "recursive_queue.h"
using namespace std;
template <typename T>
void Queue_Recur<T>::init(unsigned int size) {
  maxSize = size;
  front = -1;
  rear = -1;
  count = 0;
  items = new T[maxSize];
}

template <typename T>
void Queue_Recur<T>::copyItems(const Queue_Recur<T>& q, int index) {
  if (index < q.count) {
    items[index] = q.items[index];
    copyItems(q, index + 1);
  }
}

template <typename T>
void Queue_Recur<T>::copyQueue(const Queue_Recur<T>& q) {
  maxSize = q.maxSize;
  front = q.front;
  rear = q.rear;
  count = q.count;
  items = new T[maxSize];
  copyItems(q, 0);
}

template <typename T>
void Queue_Recur<T>::release() {
  front = -1;
  rear = -1;
  count = 0;
  delete[] items;
}

template <typename T>
bool Queue_Recur<T>::isEmpty() {
  return count == 0;
}

template <typename T>
void Queue_Recur<T>::enqueue(T data) {
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
T Queue_Recur<T>::dequeue() {
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
T Queue_Recur<T>::frontValue() {
  return items[front];
}

template <typename T>
void Queue_Recur<T>::printRecursive(int index) {
  if (index > rear) {
    return;
  }
  cout << items[index] << " ";
  printRecursive(index + 1);
}

template <typename T>
void Queue_Recur<T>::print() {
  if (isEmpty()) {
    cout << "Queue is empty, can't print" << std::endl;
    return;
  }
  cout << "Queue: ";
  printRecursive(front);
  cout << std::endl;
}