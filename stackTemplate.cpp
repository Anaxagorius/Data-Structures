#include <iostream>
#include <stack>   // Provides std::stack (a container adaptor) [1](https://en.cppreference.com/w/cpp/container/stack.html)

using namespace std;
// STUDY NOTE:
// `using namespace std;` pulls everything from namespace std into the current scope.
// This is convenient for small learning programs, but can cause name collisions in
// bigger projects; many modern style guides recommend avoiding it at global scope.
// (LearnCpp, 2025). [4](https://www.learncpp.com/cpp-tutorial/using-declarations-and-using-directives/)

int main() {
    // =========================================================================
    // std::stack: What it is (big picture)
    // -------------------------------------------------------------------------
    // std::stack is a *container adaptor* that provides a restricted interface
    // to an underlying container (by default std::deque).
    //
    // Key property: LIFO (Last-In, First-Out)
    // - The last element pushed becomes the first element popped.
    // - We can only access the "top" (most recently pushed element).
    //
    // This is exactly why stacks are used for:
    // - function call stacks, undo/redo, parsing, DFS, etc.
    // (cppreference, n.d.). [1](https://en.cppreference.com/w/cpp/container/stack.html)
    // =========================================================================

    stack<int> myStack;  // Create a stack holding integers [1](https://en.cppreference.com/w/cpp/container/stack.html)

    // =========================================================================
    // PUSH: add elements to the top
    // -------------------------------------------------------------------------
    // push(x) inserts x at the top of the stack.
    // After pushes below:
    //   Bottom -> 10, 20, 30 <- Top
    // (cppreference describes stack modifiers including push/pop). [1](https://en.cppreference.com/w/cpp/container/stack.html)
    // =========================================================================
    myStack.push(10);
    myStack.push(20);
    myStack.push(30);

    // =========================================================================
    // TOP: view the element at the top (most recent push)
    // -------------------------------------------------------------------------
    // top() returns a reference to the top element (the most recently pushed).
    //
    // IMPORTANT PRECONDITION:
    // - The stack must NOT be empty when calling top().
    // - In this program it's safe here because we just pushed 3 items.
    //
    // (cppreference: top returns reference to the top element; describes it as
    // the most recently pushed element). [2](https://en.cppreference.com/w/cpp/container/stack/top)
    // =========================================================================
    cout << "Top element: " << myStack.top() << endl;

    // =========================================================================
    // POP + LOOPING UNTIL EMPTY
    // -------------------------------------------------------------------------
    // empty() tells you whether the stack has any elements.
    // This is important because:
    // - top() and pop() have a "not empty" precondition.
    //
    // pop() removes the top element.
    // - pop() returns void (no value), so the usual pattern is:
    //     value = top(); pop();
    //
    // (cppreference: pop removes top element; effectively calls pop_back on the
    // underlying container). [3](https://en.cppreference.com/w/cpp/container/stack/pop.html)
    // (cppreference: top accesses top element). [2](https://en.cppreference.com/w/cpp/container/stack/top)
    // =========================================================================
    while (!myStack.empty()) {
        int poppedValue = myStack.top(); // Read top BEFORE removing it [2](https://en.cppreference.com/w/cpp/container/stack/top)
        myStack.pop();                   // Remove that top element [3](https://en.cppreference.com/w/cpp/container/stack/pop.html)

        cout << "Popped: " << poppedValue << endl;
    }

    // =========================================================================
    // CHECK EMPTY
    // -------------------------------------------------------------------------
    // After the loop above, we popped everything until empty() became true.
    // So now this condition should be true.
    //
    // empty() checks whether the stack contains elements.
    // (empty() is part of std::stack capacity operations). [1](https://en.cppreference.com/w/cpp/container/stack.html)
    // =========================================================================
    if (myStack.empty()) {
        cout << "Stack is empty." << endl;
    } else {
        cout << "Stack is not empty." << endl;
    }

    return 0;
}