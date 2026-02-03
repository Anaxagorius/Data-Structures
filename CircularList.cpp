#include <iostream>
using namespace std;

// Node structure
struct Node {
    int data;
    Node* next;

    Node(int value) {
        data = value;
        next = nullptr;
    }
};

// Circular Singly Linked List class
class CircularLinkedList {
private:
    Node* head;

public:
    // Constructor
    CircularLinkedList() {
        head = nullptr;
    }

    // Insert node at the end of the list
    void insertNode(int value) {
        Node* newNode = new Node(value);

        // Case 1: Empty list
        if (head == nullptr) {
            head = newNode;
            newNode->next = head;   // Point to itself (circular)
        }
        else {
            Node* current = head;

            // Traverse until last node
            while (current->next != head) {
                current = current->next;
            }

            current->next = newNode;  // Link last node to new node
            newNode->next = head;     // New node points back to head
        }
    }

    // Display the circular linked list
    void display() {
        if (head == nullptr) {
            cout << "List is empty." << endl;
            return;
        }

        Node* current = head;

        cout << "Circular Linked List: ";
        do {
            cout << current->data << " -> ";
            current = current->next;
        } while (current != head);

        cout << "(head)" << endl;
    }

    // Destructor to free memory
    ~CircularLinkedList() {
        if (head == nullptr)
            return;

        Node* current = head->next;
        Node* temp;

        while (current != head) {
            temp = current;
            current = current->next;
            delete temp;
        }

        delete head;
        head = nullptr;
    }
};

// Main function
int main() {
    CircularLinkedList list;

    list.insertNode(10);
    list.insertNode(20);
    list.insertNode(30);
    list.insertNode(40);

    list.display();

    return 0;
}
