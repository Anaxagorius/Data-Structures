#include <iostream>     // std::cout, std::endl  (I/O utilities)
#include <stdexcept>    // std::underflow_error  (optional: safer error handling)

// -----------------------------------------------------------------------------
// STUDY NOTE: "using namespace std;"
// This is common in beginner examples, but in larger projects it can cause
// name collisions because it brings *all* std names into the current scope.
// A safer style is to write std::cout, std::endl, etc. (LearnCpp, 2025). [7](https://www.learncpp.com/cpp-tutorial/using-declarations-and-using-directives/)
using namespace std;

// ============================================================================
// 1) Node: the building block of the linked list
// ----------------------------------------------------------------------------
// Each node stores:
//   - data: the integer payload
//   - next: pointer to the next node (toward the bottom of the stack)
//
// VISUAL MODEL (top at left):
//    top --> [data|next] --> [data|next] --> [data|nullptr]
// ============================================================================

struct Node {
    int data;     // payload value stored in this node
    Node* next;   // link to next node in the chain (nullptr means "end")

    // ------------------------------------------------------------------------
    // CONSTRUCTOR: member initializer list
    //
    // Why ": data(val), next(nullptr)"?
    // - Members are initialized *before* the constructor body runs.
    // - The initializer list is the correct place to do non-default initialization,
    //   and is required for members that cannot be default-initialized (e.g., const,
    //   references). (cppreference, n.d.). [1](https://tcs.rwth-aachen.de/docs/cpp/reference/en.cppreference.com/w/cpp/language/initializer_list.html)
    //
    // nullptr:
    // - Type-safe null pointer literal introduced in C++11.
    // - Converts to any pointer type safely; better than NULL/0 in many contexts.
    //   (cppreference, n.d.). [5](https://en.cppreference.com/w/cpp/language/nullptr.html)
    // ------------------------------------------------------------------------
    explicit Node(int val) : data(val), next(nullptr) {}
};

// ============================================================================
// 2) StackListImp: Stack implemented using a singly linked list
// ----------------------------------------------------------------------------
// Core idea:
// - The top of the stack is the "front" of the linked list.
// - push(val): insert at front (O(1))
// - pop(): remove from front (O(1))
// - destructor: remove everything (O(n))
//
// MEMORY NOTE:
// - This implementation uses manual dynamic allocation (new/delete).
// - That means this class *owns* heap memory and must free it.
// - If you forget delete -> memory leak.
// - If you delete twice -> undefined behavior.
// (LearnCpp, 2025). [2](https://www.learncpp.com/cpp-tutorial/dynamic-memory-allocation-with-new-and-delete/)
//
// RULE OF THREE / FIVE:
// - If you define a destructor for a type managing a raw resource (like Node*),
//   you likely must define/disable copy operations to avoid shallow copy bugs.
// (cppreference, n.d.). [3](https://en.cppreference.com/w/cpp/language/rule_of_three.html)
//
// CORE GUIDELINES CONTEXT (resource safety / RAII mindset):
// - Modern guidance encourages safer ownership patterns and careful resource
//   management to avoid leaks/dangling pointers. (Stroustrup & Sutter, 2025). [4](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines)
//
// ============================================================================

class StackListImp {
private:
    Node* top; // points to the top node; nullptr means "empty stack" [5](https://en.cppreference.com/w/cpp/language/nullptr.html)

    // ------------------------------------------------------------------------
    // clear(): helper used by destructor and move assignment
    //
    // Why have this helper?
    // - Avoid duplicating the "walk and delete nodes" logic in multiple places.
    // - Keeps destructor simple and consistent.
    //
    // Deleting nodes:
    // - delete returns heap memory allocated via new back to the system.
    // - After delete, pointers to that memory become "dangling" if still used.
    // (LearnCpp, 2025). [2](https://www.learncpp.com/cpp-tutorial/dynamic-memory-allocation-with-new-and-delete/)
    // ------------------------------------------------------------------------
    void clear() noexcept {
        while (top != nullptr) {            // nullptr is a null pointer literal [5](https://en.cppreference.com/w/cpp/language/nullptr.html)
            Node* temp = top;               // hold current node
            top = top->next;                // advance first
            delete temp;                    // free node memory (matches new) [2](https://www.learncpp.com/cpp-tutorial/dynamic-memory-allocation-with-new-and-delete/)
        }
    }

public:
    // ------------------------------------------------------------------------
    // Constructor: start with an empty stack
    // Member initializer list initializes `top` to nullptr before body runs.
    // (cppreference, n.d.). [1](https://tcs.rwth-aachen.de/docs/cpp/reference/en.cppreference.com/w/cpp/language/initializer_list.html)
    // ------------------------------------------------------------------------
    StackListImp() : top(nullptr) {}

    // ------------------------------------------------------------------------
    // RULE OF THREE / FIVE SAFETY:
    //
    // Because this class manually deletes nodes in ~StackListImp(),
    // a compiler-generated copy constructor/assignment would do a shallow copy:
    //   StackListImp a;
    //   StackListImp b = a;   // would copy only `top` pointer value
    // Then both destructors would delete the same nodes => double delete UB.
    // (cppreference, n.d.). [3](https://en.cppreference.com/w/cpp/language/rule_of_three.html)
    //
    // Option A (shown): disable copying to prevent accidental shallow copies.
    // ------------------------------------------------------------------------
    StackListImp(const StackListImp&) = delete;
    StackListImp& operator=(const StackListImp&) = delete;

    // ------------------------------------------------------------------------
    // Move constructor: "steal" the linked list from another stack safely.
    // After move, other.top must be set to nullptr to prevent double delete.
    // This is part of thinking through the "Rule of Five" when managing
    // resources manually. (cppreference, n.d.). [3](https://en.cppreference.com/w/cpp/language/rule_of_three.html)
    // ------------------------------------------------------------------------
    StackListImp(StackListImp&& other) noexcept : top(other.top) {
        other.top = nullptr; // leave moved-from object in safe empty state [5](https://en.cppreference.com/w/cpp/language/nullptr.html)
    }

    // Move assignment: clear current nodes, then steal other's nodes.
    StackListImp& operator=(StackListImp&& other) noexcept {
        if (this != &other) {
            clear();             // free current resources first [2](https://www.learncpp.com/cpp-tutorial/dynamic-memory-allocation-with-new-and-delete/)
            top = other.top;
            other.top = nullptr; // prevent double delete [5](https://en.cppreference.com/w/cpp/language/nullptr.html)
        }
        return *this;
    }

    // ------------------------------------------------------------------------
    // push(val): O(1)
    //
    // Steps:
    // 1) Allocate a new Node on the heap (dynamic memory).
    // 2) Point it to current top.
    // 3) Update top to new node.
    //
    // new/delete basics and leak risk:
    // - Memory allocated with new persists until delete is called.
    // - Forgetting delete => memory leak. (LearnCpp, 2025). [2](https://www.learncpp.com/cpp-tutorial/dynamic-memory-allocation-with-new-and-delete/)
    // ------------------------------------------------------------------------
    void push(int val) {
        Node* newNode = new Node(val); // allocate & construct node [2](https://www.learncpp.com/cpp-tutorial/dynamic-memory-allocation-with-new-and-delete/)
        newNode->next = top;           // link new node to current top
        top = newNode;                // new node becomes the new top
    }

    // ------------------------------------------------------------------------
    // pop(): O(1)
    //
    // Your original code returned -1 on empty.
    // STUDY NOTE: Returning sentinel values can be risky because -1 might be
    // a valid stack value. A safer approach is throwing an exception or using
    // std::optional<int>. (This file keeps your original behavior but comments
    // the modern alternative.)
    //
    // Underflow check:
    // - If top is nullptr, stack is empty. (cppreference, n.d.). [5](https://en.cppreference.com/w/cpp/language/nullptr.html)
    // ------------------------------------------------------------------------
    int pop() {
        if (top == nullptr) {
            cout << "Stack is empty." << endl;
            return -1; // original sentinel error value (see note above)
            // Alternative (safer API):
            // throw std::underflow_error("pop on empty stack");
        }

        int val = top->data;      // capture data to return
        Node* temp = top;         // node to remove
        top = top->next;          // move top down
        delete temp;              // free removed node to avoid leak [2](https://www.learncpp.com/cpp-tutorial/dynamic-memory-allocation-with-new-and-delete/)
        return val;
    }

    // ------------------------------------------------------------------------
    // peek(): look at the top without removing it (optional convenience)
    //
    // This method is useful for debugging and typical stack APIs.
    // It is const because it doesn't modify the stack.
    // ------------------------------------------------------------------------
    int peek() const {
        if (top == nullptr) {
            // In a real API, prefer exceptions or optional.
            // We'll print and return sentinel to stay consistent with your pop().
            cout << "Stack is empty." << endl;
            return -1;
        }
        return top->data;
    }

    // ------------------------------------------------------------------------
    // isEmpty(): O(1)
    // const because it does not modify object state.
    // ------------------------------------------------------------------------
    bool isEmpty() const {
        return top == nullptr;
    }

    // ------------------------------------------------------------------------
    // Destructor: frees all nodes
    //
    // Destructors are called automatically when an object’s lifetime ends.
    // If you allocate memory with new, you must ensure it is released, often
    // in the destructor, to prevent leaks. (Microsoft Learn, n.d.; LearnCpp, 2025). [6](https://learn.microsoft.com/en-us/cpp/cpp/destructors-cpp?view=msvc-170)[2](https://www.learncpp.com/cpp-tutorial/dynamic-memory-allocation-with-new-and-delete/)
    //
    // This destructor uses clear() to delete all nodes safely.
    // ------------------------------------------------------------------------
    ~StackListImp() {
        clear();
    }
};


// ============================================================================
// (Optional) Minimal test harness
// Uncomment main() if you want to run quick tests.
// ============================================================================

/*
int main() {
    StackListImp s;

    s.push(10);
    s.push(20);
    s.push(30);

    cout << "Peek: " << s.peek() << endl;  // expect 30
    cout << "Pop: " << s.pop() << endl;    // expect 30
    cout << "Pop: " << s.pop() << endl;    // expect 20
    cout << "Pop: " << s.pop() << endl;    // expect 10
    cout << "Pop: " << s.pop() << endl;    // empty -> prints message, returns -1

    return 0;
}
*/