# Implementing Hashing Table from scratch

Hashing Table is a data structure that stores key-value pairs. It uses a hash function to compute an index into an array of buckets or slots, from which the desired value can be found. In this Exercise 2, I implement a simple Hashing Table, using struct and template.

## Hashing Table Overview

A Hashing Table is a data structure that stores key-value pairs. It uses a hash function to compute an index into an array of buckets or slots, from which the desired value can be found. The hash function is used to transform the key into an index, so that the key can be stored in the corresponding slot. The hash function should be deterministic, meaning that it should always return the same index for the same key.

## Hashing Table Implementation

### Hashing Table by Linear Probing

In this implementation, I use linear probing to handle collisions. When a collision occurs, I search for the next available slot in the array by incrementing the index until an empty slot is found. This way, I can store multiple key-value pairs in the same slot, as long as they have different keys.

### Hashing Table by Quadratic Probing

In this implementation, I use quadratic probing to handle collisions. When a collision occurs, I search for the next available slot in the array by incrementing the index using a quadratic function until an empty slot is found. This way, I can store multiple key-value pairs in the same slot, as long as they have different keys.

### Hashing Table by Double Hashing

In this implementation, I use double hashing to handle collisions. When a collision occurs, I search for the next available slot in the array by incrementing the index using a second hash function until an empty slot is found. This way, I can store multiple key-value pairs in the same slot, as long as they have different keys.

### Hashing Table by Chaining using Linked List

In this implementation, I use chaining to handle collisions. When a collision occurs, I store the key-value pairs in a linked list at the corresponding slot in the array. This way, I can store multiple key-value pairs in the same slot, even if they have the same key.

### Hashing Table by Chaining using AVL Tree

In this implementation, I use chaining to handle collisions. When a collision occurs, I store the key-value pairs in an AVL tree at the corresponding slot in the array. This way, I can store multiple key-value pairs in the same slot, even if they have the same key.

## Hashing Table Operations

The Hashing Table supports the following operations:

- Insert: Insert a key-value pair into the Hashing Table.
- Remove: Remove a key-value pair from the Hashing Table.
- Search: Search for a key in the Hashing Table and return the corresponding value.
- Print: Print the contents of the Hashing Table.

## Hashing Table Usage

To use the Hashing Table, you can see in the main.cpp file. You can create a Hashing Table object and call the Insert, Remove, Search, and Print operations on it.

## Conclusion

In this Exercise 2, I have implemented a simple Hashing Table using different collision resolution techniques, such as linear probing, quadratic probing, double hashing, chaining using linked list, and chaining using AVL tree. The Hashing Table is a fundamental data structure in programming and is used in various applications. By understanding how it works and implementing it from scratch, you can gain a deeper insight into its underlying principles and improve your programming skills.

