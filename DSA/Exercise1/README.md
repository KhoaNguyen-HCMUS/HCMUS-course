# Implementing Stack and Queue from scratch

Stack and Queue are two fundamental data structures in programming. Stack allows adding and retrieving elements according to the LIFO (Last In, First Out) principle, while Queue allows adding and retrieving elements according to the FIFO (First In, First Out) principle. In this Exercise 1, I implement these two data structures, using struct and template.

## Stack Overview

A Stack is a data structure that stores elements in a Last In, First Out (LIFO) order. It has two main operations: Push, which adds an element to the top of the stack, and Pop, which removes the top element from the stack. The Peek operation allows you to view the top element without removing it.

## Stack Implementation

### Stack using Array

In this implementation, I use an array to store the elements of the stack. I keep track of the top element using an index variable, and increment it when pushing elements and decrement it when popping elements. This way, I can add and remove elements in constant time.

### Stack using Linked List

In this implementation, I use a linked list to store the elements of the stack. I keep track of the top element using a pointer to the head of the list. When pushing elements, I add a new node to the head of the list, and when popping elements, I remove the head node. This way, I can add and remove elements in constant time.

## Stack Operations

The Stack supports the following operations:

- Push: Add an element to the top of the stack.

- Pop: Remove the top element from the stack.

## Queue Overview

A Queue is a data structure that stores elements in a First In, First Out (FIFO) order. It has two main operations: Enqueue, which adds an element to the back of the queue, and Dequeue, which removes the front element from the queue. The Peek operation allows you to view the front element without removing it.

## Queue Implementation

### Queue using Array

In this implementation, I use an array to store the elements of the queue. I keep track of the front and back of the queue using two index variables, and increment them accordingly when adding or removing elements. This way, I can add and remove elements in constant time.

### Queue using Linked List

In this implementation, I use a linked list to store the elements of the queue. I keep track of the front and back of the queue using pointers to the head and tail of the list. When adding elements, I add a new node to the tail of the list, and when removing elements, I remove the head node. This way, I can add and remove elements in constant time.

## Queue Operations

The Queue supports the following operations:

- Enqueue: Add an element to the back of the queue.

- Dequeue: Remove the front element from the queue.

## Stack and Queue Usage

To use the Stack and Queue, you can see in the main.cpp file. You can create a Stack or Queue object and call the Push, Pop, Enqueue, Dequeue operations on it.

## Conclusion

In this Exercise 1, I have implemented the Stack and Queue data structures using both array and linked list. These data structures are fundamental in programming and are used in various applications. By understanding how they work and implementing them from scratch, you can gain a deeper insight into their underlying principles and improve your programming skills.
