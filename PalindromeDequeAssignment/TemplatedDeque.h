# Templated Deque Header File

#ifndef TEMPLATED_DEQUE_H
#define TEMPLATED_DEQUE_H

#include <iostream>
#include <memory>

// Node structure for doubly linked list
template <typename T>
struct Node {
    T data;
    Node* next;
    Node* prev;
    Node(T value) : data(value), next(nullptr), prev(nullptr) {}  
};

// Templated Deque class
template <typename T>
class TemplatedDeque {
private:
    Node<T>* front;
    Node<T>* rear;
public:
    TemplatedDeque() : front(nullptr), rear(nullptr) {}
    ~TemplatedDeque() { while (!isEmpty()) deleteFront(); }

    void insertFront(T value) {
        Node<T>* newNode = new Node<T>(value);
        if (isEmpty()) {
            front = rear = newNode;
        } else {
            newNode->next = front;
            front->prev = newNode;
            front = newNode;
        }
    }

    void insertRear(T value) {
        Node<T>* newNode = new Node<T>(value);
        if (isEmpty()) {
            front = rear = newNode;
        } else {
            newNode->prev = rear;
            rear->next = newNode;
            rear = newNode;
        }
    }

    void deleteFront() {
        if (!isEmpty()) {
            Node<T>* temp = front;
            front = front->next;
            if (front)
                front->prev = nullptr;
            else
                rear = nullptr;
            delete temp;
        }
    }

    void deleteRear() {
        if (!isEmpty()) {
            Node<T>* temp = rear;
            rear = rear->prev;
            if (rear)
                rear->next = nullptr;
            else
                front = nullptr;
            delete temp;
        }
    }

    bool isEmpty() const {
        return front == nullptr;
    }
};

#endif // TEMPLATED_DEQUE_H
