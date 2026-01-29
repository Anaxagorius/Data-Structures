#include <iostream>

using namespace std;

// ────────────────────────────────────────────────
// Node structure (good style: use member initializer list)
struct Node {
    int   data;
    Node* next;

    explicit Node(int val) : data(val), next(nullptr) {}
};

// ────────────────────────────────────────────────
class LinkedList {
private:                    // ← better encapsulation
    Node* head;

public:
    LinkedList() : head(nullptr) {}

    // VERY IMPORTANT: destructor to prevent memory leak
    ~LinkedList() {
        Node* current = head;
        while (current != nullptr) {
            Node* next = current->next;
            delete current;
            current = next;
        }
    }

    // Optional: disable copying (simplest safe choice)
    LinkedList(const LinkedList&) = delete;
    LinkedList& operator=(const LinkedList&) = delete;

    void insertAtEnd(int val) {
        Node* newNode = new Node(val);

        if (head == nullptr) {
            head = newNode;
            return;
        }

        else{
        Node* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = newNode;
        }
    }

    void insertAtBeggining(int val) {//function to insert a new node at the beginning of the linked list
        Node* newNode = new Node(val);//create a new node with the given value
        newNode->next = head;//point the new node's next to the current head
        head = newNode;//set the head to the new node
    }

    // Nice helper for printing (using modern C++ style)
    void print() const {
        const Node* temp = head;
        while (temp != nullptr) {
            cout << temp->data;
            if (temp->next != nullptr) cout << "  ";
            temp = temp->next;
        }
        cout << '\n';
    }

    bool searchNode(int searchVal) const {//function to search for a node with a specific value in the linked list
        Node* temp = head;//start from the head of the list
        while (temp != nullptr) {//traverse the list until the end
            if (temp->data == searchVal) {//if the current node's data matches the search value
                return true;//return true indicating the node is found
            }
            temp = temp->next;//move to the next node
        }
        return false;//if the search value is not found, return false
    }
};

// ────────────────────────────────────────────────
// main() MUST be outside the class
int main() {
    LinkedList list;

    list.insertAtEnd(10);
    list.insertAtEnd(20);
    list.insertAtEnd(30);
    list.insertAtEnd(40);
    list.insertAtEnd(50);

    cout << "Linked List: ";
    list.print();

    // List is automatically cleaned up when main() ends
    return 0;
}