
/*#include <iostream>
using namespace std;

// Node structure for Doubly Linked List
struct Node {
    int data;       // Value of the node
    Node* next;     // Pointer to the next node
    Node* prev;     // Pointer to the previous node

    // Initialize a node inside the constructor
    Node(int val) {
        data = val;
        next = nullptr;
        prev = nullptr;
    }
};

// Class to represent the Doubly Linked List and its operations
class DoublyLinkedListImplementation {
public:
    Node* head;     // Pointer to the head of the list

    // Constructor to initialize the list
    DoublyLinkedListImplementation() {
        head = nullptr;
    }

    // Destructor to deallocate memory
    ~DoublyLinkedListImplementation() {
        Node* current = head;
        Node* nextNode = nullptr;
        
        while (current != nullptr) {
            nextNode = current->next;
            delete current;
            current = nextNode;
        }
    }

    // Insert at the front
    void insertAtFront(int val) {
        Node* newNode = new Node(val);

        if (head != nullptr) {
            newNode->next = head;
            head->prev = newNode;
        }

        head = newNode;
    }

    // Insert at the end
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
        newNode->prev = temp;
    }

    //insert at end

    void insertatBeginning(int value) {
    Node* newNode = new Node (value);
    
    if (head != nullptr) {
    head->prev = newNode;
    
    newNode-> = head;
    
    head = newNode;
    }

    // Display list forward
    void displayForward() {
        Node* temp = head;
        cout << "List (Forward): ";
        while (temp != nullptr) {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    }

    // Display list backward
    void displayBackward() {
        if (head == nullptr) {
            cout << "List is empty." << endl;
            return;
        }

        Node* temp = head;

        // Move to last node
        while (temp->next != nullptr) {
            temp = temp->next;
        }

        cout << "List (Backward): ";
        while (temp != nullptr) {
            cout << temp->data << " ";
            temp = temp->prev;
        }
        cout << endl;
    }
};

// Main function
int main() {
    DoublyLinkedListImplementation dll;

    dll.insertAtFront(10);
    dll.insertAtFront(20);
    dll.insertAtEnd(5);

    dll.displayForward();
    dll.displayBackward();

    return 0;
}


#include <iostream>
using namespace std;*/

#include <iostream>
using namespace std;

/*
    ============================================
    DOUBLY LINKED LIST STUDY GUIDE (C++)
    ============================================

    A doubly linked list node has:
      - data
      - next pointer (to the node after it)
      - prev pointer (to the node before it)

    Why it matters:
      - Insertion/deletion in the middle requires updating BOTH directions.
*/

struct Node {
    int data;
    Node* next;
    Node* prev;

    Node(int val) : data(val), next(nullptr), prev(nullptr) {}
};

class DoublyLinkedList {
private:
    Node* head;

    // ------------------------------------------------------------
    // Helper: Get pointer to node at 1-based position (pos)
    // Returns nullptr if pos is out of range.
    // ------------------------------------------------------------
    Node* getNodeAtPosition(int pos) {
        if (pos < 1) return nullptr;
        Node* cur = head;
        int idx = 1;
        while (cur != nullptr && idx < pos) {
            cur = cur->next;
            idx++;
        }
        return cur; // may be nullptr if pos > length
    }

public:
    // ------------------------------------------------------------
    // Constructor / Destructor
    // ------------------------------------------------------------
    DoublyLinkedList() : head(nullptr) {}

    ~DoublyLinkedList() {
        Node* cur = head;
        while (cur != nullptr) {
            Node* nxt = cur->next;
            delete cur;          // release memory for each node
            cur = nxt;
        }
        head = nullptr;
    }

    // ------------------------------------------------------------
    // Helper: Insert at front (used by insertAtPosition)
    // ------------------------------------------------------------
    void insertAtFront(int val) {
        Node* newNode = new Node(val);

        newNode->next = head;      // new node points forward to old head
        newNode->prev = nullptr;   // new head has no previous

        if (head != nullptr) {
            head->prev = newNode;  // old head points back to new head
        }

        head = newNode;            // update head to new node
    }

    // ------------------------------------------------------------
    // Helper: Display forward (study / debugging)
    // ------------------------------------------------------------
    void displayForward() const {
        cout << "Forward: ";
        Node* cur = head;
        while (cur != nullptr) {
            cout << cur->data << " ";
            cur = cur->next;
        }
        cout << "\n";
    }

    // ------------------------------------------------------------
    // Helper: Display backward (study / debugging)
    // ------------------------------------------------------------
    void displayBackward() const {
        cout << "Backward: ";
        if (head == nullptr) {
            cout << "(empty)\n";
            return;
        }

        // go to tail
        Node* tail = head;
        while (tail->next != nullptr) tail = tail->next;

        // traverse backward
        while (tail != nullptr) {
            cout << tail->data << " ";
            tail = tail->prev;
        }
        cout << "\n";
    }

    // ============================================================
    // ✅ FUNCTION 1: INSERT AT POSITION (1-based)
    // ============================================================
    /*
        insertAtPosition(pos, val)

        Goal:
          Insert a new node containing val at position pos (1-based).

        Examples:
          List: 10 <-> 20 <-> 30
          insertAtPosition(1, 99) => 99 <-> 10 <-> 20 <-> 30
          insertAtPosition(3, 99) => 10 <-> 20 <-> 99 <-> 30

        Key pointer updates (middle insertion):
          newNode->next = current
          newNode->prev = previous
          previous->next = newNode
          current->prev = newNode

        Returns:
          true  = inserted successfully
          false = invalid position (pos > length+1 or pos < 1)
    */
    bool insertAtPosition(int pos, int val) {
        // Case A: invalid position
        if (pos < 1) return false;

        // Case B: insert at head (pos == 1)
        if (pos == 1) {
            insertAtFront(val);
            return true;
        }

        /*
            For pos > 1:
              - We need the node currently at position pos (call it current)
              - And the node before it (position pos-1, call it previous)

            If current is nullptr, we might still insert at the end
            ONLY if previous exists and pos == length+1.
        */
        Node* previous = getNodeAtPosition(pos - 1);
        if (previous == nullptr) {
            // Means pos-1 doesn't exist => pos too large
            return false;
        }

        Node* current = previous->next;  // could be nullptr if inserting at end
        Node* newNode = new Node(val);

        // Link new node with its neighbors
        newNode->prev = previous;
        newNode->next = current;

        // Link previous forward to new node
        previous->next = newNode;

        // If we are not inserting at the end, link current back to new node
        if (current != nullptr) {
            current->prev = newNode;
        }

        return true;
    }

    // ============================================================
    // ✅ FUNCTION 2: DELETE BY VALUE (first occurrence)
    // ============================================================
    /*
        deleteByValue(target)

        Goal:
          Delete the FIRST node whose data == target.

        Strategy:
          1) Traverse from head to find the node.
          2) Once found, re-link its neighbors:
               - if node is head: head = head->next
               - if node has prev: node->prev->next = node->next
               - if node has next: node->next->prev = node->prev
          3) delete the node to free memory

        Returns:
          true  = node found and deleted
          false = target not found (no deletion)
    */
    bool deleteByValue(int target) {
        Node* cur = head;

        // Step 1: Find the node
        while (cur != nullptr && cur->data != target) {
            cur = cur->next;
        }

        // Not found
        if (cur == nullptr) return false;

        // Step 2: Re-link neighbors

        // If deleting head:
        if (cur == head) {
            head = cur->next;            // move head forward
            if (head != nullptr) {
                head->prev = nullptr;    // new head has no prev
            }
        } else {
            // Middle or tail deletion: cur->prev must exist here
            cur->prev->next = cur->next; // skip cur moving forward

            // If cur is not the last node:
            if (cur->next != nullptr) {
                cur->next->prev = cur->prev; // skip cur moving backward
            }
        }

        // Step 3: Free memory
        delete cur;

        return true;
    }

    // ============================================================
    // ✅ FUNCTION 3: DELETE AT POSITION (1-based)
    // ============================================================
    /*
        deleteAtPosition(pos)

        Goal:
          Delete the node located at position pos (1-based).

        Strategy:
          1) Locate the node at pos.
          2) If pos == 1, update head.
          3) Otherwise unlink:
               node->prev->next = node->next
               if node->next != nullptr:
                   node->next->prev = node->prev
          4) delete node

        Returns:
          true  = deletion successful
          false = invalid pos (out of range)
    */
    bool deleteAtPosition(int pos) {
        if (pos < 1) return false;

        Node* toDelete = getNodeAtPosition(pos);
        if (toDelete == nullptr) return false; // pos out of range

        // If deleting head
        if (toDelete == head) {
            head = toDelete->next;
            if (head != nullptr) {
                head->prev = nullptr;
            }
            delete toDelete;
            return true;
        }

        // Deleting middle or tail
        Node* left = toDelete->prev;
        Node* right = toDelete->next;

        // Bridge left -> right
        if (left != nullptr) left->next = right;

        // Bridge right -> left (if right exists)
        if (right != nullptr) right->prev = left;

        delete toDelete;
        return true;
    }

    //Delete node from beginning
    void deleteFromBeginning() {
        if (head == nullptr) return; // List is empty

        Node* toDelete = head;
        head = head->next; // Move head forward

        if (head != nullptr) {
            head->prev = nullptr; // New head has no previous
        }

        delete toDelete; // Free memory
    }

    // ============================================================
    // ✅ FUNCTION 4: SEARCH AND INSERT (insert AFTER found value)
    // ============================================================
    /*
        searchAndInsert(searchVal, newVal)

        Goal:
          Search for the FIRST node with data == searchVal,
          then insert a new node (newVal) immediately AFTER it.

        Example:
          10 <-> 20 <-> 30
          searchAndInsert(20, 99)
          => 10 <-> 20 <-> 99 <-> 30

        Pointer updates (insert-after):
          found = node with searchVal
          after = found->next

          newNode->prev = found
          newNode->next = after
          found->next   = newNode
          if (after != nullptr) after->prev = newNode

        Returns:
          true  = found and inserted
          false = searchVal not found
    */
    bool searchAndInsert(int searchVal, int newVal) {
        Node* cur = head;

        // Step 1: Search
        while (cur != nullptr && cur->data != searchVal) {
            cur = cur->next;
        }

        // Not found
        if (cur == nullptr) return false;

        // Step 2: Insert AFTER cur
        Node* after = cur->next;
        Node* newNode = new Node(newVal);

        newNode->prev = cur;
        newNode->next = after;

        cur->next = newNode;

        if (after != nullptr) {
            after->prev = newNode;
        }

        return true;
    }
};

// ------------------------------------------------------------
// Demo main() (optional)
// ------------------------------------------------------------
int main() {
    DoublyLinkedList dll;

    dll.insertAtPosition(1, 10);
    dll.insertAtPosition(2, 20);
    dll.insertAtPosition(3, 30);
    dll.insertAtPosition(4, 40);

    dll.displayForward();
    dll.displayBackward();

    dll.insertAtPosition(3, 99);
    cout << "\nAfter insertAtPosition(3, 99):\n";
    dll.displayForward();

    dll.searchAndInsert(20, 77);
    cout << "\nAfter searchAndInsert(20, 77):\n";
    dll.displayForward();

    dll.deleteByValue(30);
    cout << "\nAfter deleteByValue(30):\n";
    dll.displayForward();

    dll.deleteAtPosition(2);
    cout << "\nAfter deleteAtPosition(2):\n";
    dll.displayForward();

    return 0;
}

/*
============================================================
APA CITATIONS (BY FUNCTION) — COMMENTED AS REQUESTED
============================================================

insertAtPosition():
  - GeeksforGeeks. (2025, December 12). Insertion in a doubly linked list.
    https://www.geeksforgeeks.org/dsa/introduction-and-insertion-in-a-doubly-linked-list/
  - OpenDSA. (n.d.). Doubly linked lists (ListDouble).
    https://opendsa.org/OpenDSA/Books/Everything/html/ListDouble.html 

deleteByValue():
  - GeeksforGeeks. (2025, December 12). Deletion in a doubly linked list.
    https://www.geeksforgeeks.org/dsa/delete-a-node-in-a-doubly-linked-list/
  - Microsoft Learn. (n.d.). delete Operator (C++).
    https://learn.microsoft.com/en-us/cpp/cpp/delete-operator-cpp?view=msvc-170

deleteAtPosition():
  - GeeksforGeeks. (2025, December 12). Deletion in a doubly linked list.
    https://www.geeksforgeeks.org/dsa/delete-a-node-in-a-doubly-linked-list/
  - OpenDSA. (n.d.). Doubly linked lists (ListDouble).
    https://opendsa.org/OpenDSA/Books/Everything/html/ListDouble.html

searchAndInsert():
  - GeeksforGeeks. (2025, December 12). Insertion in a doubly linked list.
    https://www.geeksforgeeks.org/dsa/introduction-and-insertion-in-a-doubly-linked-list/
  - OpenDSA. (n.d.). Doubly linked lists (ListDouble).
    https://opendsa.org/OpenDSA/Books/Everything/html/ListDouble.html
============================================================
*/
