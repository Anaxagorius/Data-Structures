
#include <iostream>
using namespace std;

class Node {
public:
    int data;
    Node* next;

    Node(int val) {
        data = val;
        next = nullptr;
    }
};

class LinkedListImplementation {
private:
    Node* head;

public:
    LinkedListImplementation() {
        head = nullptr;
    }

    // Insert at end (simple helper)
    void insertAtEnd(int val) {
        Node* newNode = new Node(val);

        if (head == nullptr) {
            head = newNode;
            return;
        }

        Node* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = newNode;
    }

    // Function 05: Search for a value and insert a new node after that value
    bool searchAndInsert(int searchVal, int newVal) {
        Node* current = head; // Start at the head

        while (current != nullptr) {
            if (current->data == searchVal) {

                // Create the new node
                Node* newNode = new Node(newVal);

                // Insert after the found node
                newNode->next = current->next;
                current->next = newNode;

                return true; // Insertion successful
            }

            current = current->next; // Move to next node
        }

        return false; // Value not found
    }

    //Function 06: Delete or deallocate memories
    ~LinkedListImplementation() {
        //Destructor to deallocate memory
        Node* temp = head;
        Node* nextNode = nullptr;

        while (temp != nullptr) {
            nextNode = temp->next;
            delete temp;
            temp = nextNode;
        }
    }

    //Function 07: Delete from a given node value
    void deleteNode(int value) {
        if (head == nullptr){
            cout << "List is empty. Cannot delete." << endl;
            return;
        }

        Node* current = head;
        //Traverse the list to find the node with the given value
        Node* prev = nullptr;
        while (current != nullptr && current->data != value) {
            prev = current;
            current = current->next;
        }

        //If value is not found
        if (current == nullptr) {
            cout <<"Value not found in the list." << endl;
            return;
        }

        //If deleting the head node
        if (prev == nullptr) {
            head = current->next;
        } else {
            //Update the previous nodes next pointer to skip the current node
            prev->next = current->next;
        }

        //Free the memory of the node to be deleted
        delete current;
    }

    // Display list (helper)
    void display() {
        Node* current = head;
        while (current != nullptr) {
            cout << current->data << " -> ";
            current = current->next;
        }
        cout << "NULL\n";
    }

};

int main() {
    LinkedListImplementation list;

    list.insertAtEnd(10);
    list.insertAtEnd(20);
    list.insertAtEnd(30);

    cout << "Initial List:\n";
    list.display();

    if (list.searchAndInsert(20, 99)) {
        cout << "After inserting 99 after 20:\n";
    } else {
        cout << "Value not found.\n";
    }

    list.display();

    return 0;
}
