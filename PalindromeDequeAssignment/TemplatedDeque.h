// Templated Deque Header File
#ifndef TEMPLATED_DEQUE_H
#define TEMPLATED_DEQUE_H

#include <stdexcept> // for std::runtime_error

/*
Why a generic (templated) deque matters:
- Reusability: the same deque implementation works for char, int, double, or user-defined types.
- Type-safety: the compiler enforces correct types at compile time (no casting / void*).
- Maintainability: you implement and debug the deque once instead of rewriting it per data type.
*/

// Node structure for a doubly linked list (supports traversal both directions)
template <typename T>
struct Node {
    T data;
    Node* next;
    Node* prev;
    explicit Node(const T& value) : data(value), next(nullptr), prev(nullptr) {}
};

// Templated Deque class implemented using a doubly linked list
template <typename T>
class TemplatedDeque {
private:
    Node<T>* front_;
    Node<T>* rear_;

public:
    TemplatedDeque() : front_(nullptr), rear_(nullptr) {}

    ~TemplatedDeque() {
        while (!isEmpty()) {
            deleteFront();
        }
    }

    bool isEmpty() const { return front_ == nullptr; }

    // Insert element at the front (O(1))
    void insertFront(const T& value) {
        Node<T>* newNode = new Node<T>(value);
        if (isEmpty()) {
            front_ = rear_ = newNode;
        } else {
            newNode->next = front_;
            front_->prev = newNode;
            front_ = newNode;
        }
    }

    // Insert element at the rear (O(1))
    void insertRear(const T& value) {
        Node<T>* newNode = new Node<T>(value);
        if (isEmpty()) {
            front_ = rear_ = newNode;
        } else {
            newNode->prev = rear_;
            rear_->next = newNode;
            rear_ = newNode;
        }
    }

    // Delete element from the front and RETURN it (O(1))
    T deleteFront() {
        if (isEmpty()) {
            throw std::runtime_error("deleteFront() called on empty deque");
        }

        Node<T>* temp = front_;
        T removedValue = temp->data;

        front_ = front_->next;
        if (front_) {
            front_->prev = nullptr;
        } else {
            // deque became empty
            rear_ = nullptr;
        }

        delete temp;
        return removedValue;
    }

    // Delete element from the rear and RETURN it (O(1))
    T deleteRear() {
        if (isEmpty()) {
            throw std::runtime_error("deleteRear() called on empty deque");
        }

        Node<T>* temp = rear_;
        T removedValue = temp->data;

        rear_ = rear_->prev;
        if (rear_) {
            rear_->next = nullptr;
        } else {
            // deque became empty
            front_ = nullptr;
        }

        delete temp;
        return removedValue;
    }
};

#endif // TEMPLATED_DEQUE_H
