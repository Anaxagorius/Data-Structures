# Templated Deque Implementation

#ifndef TEMPLATED_DEQUE_H
#define TEMPLATED_DEQUE_H

template <typename T>
class Deque {
private:
    struct Node {
        T data;
        Node* prev;
        Node* next;
        Node(T value) : data(value), prev(nullptr), next(nullptr) {}
    };
    Node* front;
    Node* rear;
public:
    Deque() : front(nullptr), rear(nullptr) {}

    void insertFront(T value) {
        Node* newNode = new Node(value);
        if (isEmpty()) {
            front = rear = newNode;
        } else {
            newNode->next = front;
            front->prev = newNode;
            front = newNode;
        }
    }

    void insertRear(T value) {
        Node* newNode = new Node(value);
        if (isEmpty()) {
            front = rear = newNode;
        } else {
            newNode->prev = rear;
            rear->next = newNode;
            rear = newNode;
        }
    }

    T deleteFront() {
        if (isEmpty()) throw std::runtime_error("Deque is empty");
        T value = front->data;
        Node* temp = front;
        front = front->next;
        if (front) front->prev = nullptr;
        else rear = nullptr;
        delete temp;
        return value;
    }

    T deleteRear() {
        if (isEmpty()) throw std::runtime_error("Deque is empty");
        T value = rear->data;
        Node* temp = rear;
        rear = rear->prev;
        if (rear) rear->next = nullptr;
        else front = nullptr;
        delete temp;
        return value;
    }

    bool isEmpty() const {
        return front == nullptr;
    }
};

#endif // TEMPLATED_DEQUE_H