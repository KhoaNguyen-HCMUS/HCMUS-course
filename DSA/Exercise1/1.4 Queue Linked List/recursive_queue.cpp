#include "recursive_queue.h"

#include <iostream>
using namespace std;

template <typename T>
void Queue_Recur<T>::init() {
  front = rear = nullptr;
}

template <typename T>
typename Queue_Recur<T>::Node* Queue_Recur<T>::copyQueueRecursively(
    Node* node) {
  if (node == nullptr) {
    return nullptr;
  }
  Node* newNode = new Node;
  newNode->data = node->data;
  newNode->next = copyQueueRecursively(node->next);
  return newNode;
}

template <typename T>
void Queue_Recur<T>::copyQueue(Queue_Recur<T>& source) {
  this->release();
  this->front = this->copyQueueRecursively(source.front);
  Node* temp = this->front;
  while (temp != nullptr && temp->next != nullptr) {
    temp = temp->next;
  }
  this->rear = temp;
}

template <typename T>
void Queue_Recur<T>::releaseRecursively(Node* node) {
  if (node == nullptr) {
    return;
  }
  releaseRecursively(node->next);
  delete node;
}

template <typename T>
void Queue_Recur<T>::release() {
  releaseRecursively(front);
  front = rear = nullptr;
}

template <typename T>
bool Queue_Recur<T>::isEmpty() {
  return front == nullptr;
}

template <typename T>
void Queue_Recur<T>::enqueue(T newItem) {
  Node* newNode = new Node;
  newNode->data = newItem;
  newNode->next = nullptr;
  if (isEmpty()) {
    front = rear = newNode;
  } else {
    rear->next = newNode;
    rear = newNode;
  }
}

template <typename T>
T Queue_Recur<T>::dequeue() {
  if (isEmpty()) {
    cout << "Queue is empty" << endl;
    return T();
  }
  Node* temp = front;
  T value = front->data;
  front = front->next;
  delete temp;
  return value;
}

template <typename T>
T Queue_Recur<T>::frontValue() {
  if (isEmpty()) {
    cout << "Queue is empty" << endl;
    return T();
  }
  return front->data;
}

template <typename T>
void Queue_Recur<T>::printRecursively(Node* node) {
  if (node == nullptr) {
    return;
  }
  cout << node->data << " ";
  printRecursively(node->next);
}

template <typename T>
void Queue_Recur<T>::print() {
  if (isEmpty()) {
    cout << "Queue is empty, can't print." << endl;
    return;
  }
  cout << "Queue: ";
  printRecursively(front);
  cout << endl;
}