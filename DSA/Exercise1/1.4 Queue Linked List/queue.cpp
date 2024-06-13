#include "queue.h"

#include <iostream>
using namespace std;

template <typename T>
void Queue<T>::init() {
  front = rear = nullptr;
}

template <typename T>
void Queue<T>::copyQueue(Queue<T>& src) {
  this->release();
  Node* temp = src.front;
  while (temp != nullptr) {
    Node* newNode = new Node;
    newNode->data = temp->data;
    newNode->next = nullptr;
    if (this->rear == nullptr) {
      this->front = this->rear = newNode;
    } else {
      this->rear->next = newNode;
      this->rear = newNode;
    }
    temp = temp->next;
  }
}

template <typename T>
void Queue<T>::release() {
  while (!isEmpty()) {
    dequeue();
  }
}

template <typename T>
bool Queue<T>::isEmpty() {
  return front == nullptr;
}

template <typename T>
void Queue<T>::enqueue(T newItem) {
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
T Queue<T>::dequeue() {
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
T Queue<T>::frontValue() {
  if (isEmpty()) {
    cout << "Queue is empty" << endl;
    return T();
  }
  return front->data;
}

template <typename T>
void Queue<T>::print() {
  if (isEmpty()) {
    cout << "Queue is empty, can't print." << endl;
    return;
  }
  Node* temp = front;
  while (temp != nullptr) {
    cout << temp->data << " ";
    temp = temp->next;
  }
  cout << endl;
}