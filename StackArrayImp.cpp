#include <iostream>
using namespace std;

#define MAX 25   // Maximum size of the stack

class StackArrayImplementation {
private:
    int ArrayStack[MAX];   // Fixed-size array
    int top;               // Index of top element

public:
    // Constructor
    StackArrayImplementation() {
        top = -1;  // Stack is empty initially
    }

    // Push an element onto the stack
    void push(int value) {
        if (top == MAX - 1) {
            cout << "Stack is full. Cannot add more elements!" << endl;
        } else {
            top++;
            ArrayStack[top] = value;
            cout << "Added " << value << " to the stack." << endl;
        }
    }

    // Pop an element from the stack
    int pop() {
        if (top == -1) {
            cout << "Stack is empty. Nothing to pop!" << endl;
            return -1; // Return a sentinel value for empty stack
        } else {
            int poppedValue = ArrayStack[top];
            top--;
            cout << "Removed " << poppedValue << " from the stack." << endl;
            return poppedValue;
        }
    }

    // Peek the top element
    void peek() {
        if (top == -1) {
            cout << "Stack is empty. No top element." << endl;
        } else {
            cout << "Top element: " << ArrayStack[top] << endl;
        }
    }

    int peek() const {
        if (top == -1) {
            cout << "Stack is empty. No top element." << endl;
            return -1; // Return a sentinel value for empty stack
        } else {
            return ArrayStack[top];
        }
    }

    // Check if stack is empty
    bool isEmpty() const {
        return top == -1;
    }

    // Display stack elements
    void display() {
        if (top == -1) {
            cout << "Stack is empty." << endl;
            return;
        }

        cout << "Stack elements: ";
        for (int i = top; i >= 0; i--) {
            cout << ArrayStack[i] << " ";
        }
        cout << endl;
    }
};

// Main function
int main() {
    StackArrayImplementation s;

    s.push(10);
    s.push(20);
    s.push(30);

    s.display();
    s.peek();

    s.pop();

    if (s.isEmpty()) {
        cout << "Stack is empty." << endl;
    } else {
        cout << "Stack is not empty." << endl;
    }

    s.display();

    return 0;
}