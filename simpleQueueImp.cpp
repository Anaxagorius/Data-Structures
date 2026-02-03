#include <iostream>
using namespace std;

// ============================================================================
// STUDY NOTE: `using namespace std;`
// ----------------------------------------------------------------------------
// This is common in beginner examples because it keeps code shorter (cout instead
// of std::cout). However, in larger projects it can cause naming collisions
// because it imports *all* names from std into the current scope.
// (Stack Overflow, 2024). [4](https://stackoverflow.com/questions/4872373/why-is-including-using-namespace-into-a-header-file-a-bad-idea-in-c)
//
// For coursework examples, it's usually acceptable. For production code, prefer:
//   std::cout << "...";
// ============================================================================


// ============================================================================
// SimpleQueue (Array-Based, Fixed-Size Queue) — STUDY GUIDE VERSION
// ----------------------------------------------------------------------------
// BIG IDEA: Queue = FIFO (First-In, First-Out)
// - The first element inserted is the first element removed.
// - Enqueue adds at the REAR (end).
// - Dequeue removes from the FRONT (beginning).
// (GeeksforGeeks, 2025; Tutorialspoint, n.d.). [1](https://cplusplus.com/doc/tutorial/dynamic/)[2](https://en.cppreference.com/w/cpp/language/namespace.html)
//
// HOW THIS IMPLEMENTATION WORKS:
// - Uses a fixed-size array (capacity is MAX_SIZE).
// - Uses two indices:
//     front -> index of the current front element (next to remove)
//     rear  -> index of the current rear element (last inserted)
//
// EMPTY STATE:
// - front = -1 and rear = -1 means "nothing has ever been enqueued yet".
// - Also, if front > rear, that means we've dequeued past the last element,
//   so the queue is logically empty.
//
// IMPORTANT LIMITATION (VERY TEST-WORTHY):
// This is a simple LINEAR queue, not a circular queue.
// - Once rear reaches MAX_SIZE - 1, it reports overflow.
// - This can happen even if there is unused space at the beginning of the array
//   after multiple dequeues.
// A circular queue fixes this by wrapping indices around (mod arithmetic).
// (GeeksforGeeks, 2025; ProgramGuru, n.d.). [1](https://cplusplus.com/doc/tutorial/dynamic/)[3](https://intellipaat.com/blog/new-and-delete-operators-in-cpp/)
//
// TIME COMPLEXITY (in this version):
// - enqueue: O(1)  (just index math + assignment)
// - dequeue: O(1)  (just index math + read)
// - peek:    O(1)
// - display: O(n)  (prints all elements in range)
// (Array-based queue operations described in common references). [1](https://cplusplus.com/doc/tutorial/dynamic/)[2](https://en.cppreference.com/w/cpp/language/namespace.html)
//
// API NOTE (Sentinel Return):
// dequeue() and peek() return -1 on underflow/empty.
// This can be unsafe if -1 is a valid queue value; modern designs may use
// exceptions or std::optional<int>. We keep -1 for least impact.
// (Overflow/underflow discussion appears in array-queue explanations). [1](https://cplusplus.com/doc/tutorial/dynamic/)
// ============================================================================

class SimpleQueue {
    static const int MAX_SIZE = 10;   // Capacity (fixed size) [1](https://cplusplus.com/doc/tutorial/dynamic/)
    int queue_array[MAX_SIZE];        // Storage for queue elements
    int front;                        // Front index (next to be dequeued)
    int rear;                         // Rear index  (last enqueued)

public:
    // ------------------------------------------------------------------------
    // Constructor: initialize empty queue
    //
    // Convention:
    // - front = rear = -1 indicates "empty/unused".
    // This is a common approach in simple array queue implementations.
    // (Tutorialspoint, n.d.). [2](https://en.cppreference.com/w/cpp/language/namespace.html)
    // ------------------------------------------------------------------------
    SimpleQueue() {
        front = -1;
        rear = -1;
    }

    // ------------------------------------------------------------------------
    // isFull(): overflow check
    //
    // In this LINEAR design:
    // - the queue is "full" when rear hits the last array index.
    // - it does NOT reuse freed space at the front.
    // (GeeksforGeeks, 2025). [1](https://cplusplus.com/doc/tutorial/dynamic/)
    // ------------------------------------------------------------------------
    bool isFull() const {
        return (rear == MAX_SIZE - 1);
    }

    // ------------------------------------------------------------------------
    // isEmpty(): empty check
    //
    // Queue is empty when:
    // - front == -1 (nothing ever enqueued), OR
    // - front > rear (we dequeued everything)
    // (Tutorialspoint, n.d.). [2](https://en.cppreference.com/w/cpp/language/namespace.html)
    // ------------------------------------------------------------------------
    bool isEmpty() const {
        return (front == -1 || front > rear);
    }

    // ------------------------------------------------------------------------
    // enqueue(data): insert at REAR
    //
    // FIFO rule: elements enter at the rear/end of the queue.
    // (GeeksforGeeks, 2025). [1](https://cplusplus.com/doc/tutorial/dynamic/)
    //
    // Steps:
    // 1) If full -> overflow
    // 2) If first insert -> set front = 0
    // 3) rear++
    // 4) store element at queue_array[rear]
    // ------------------------------------------------------------------------
    void enqueue(int data) {
        if (isFull()) {
            cout << "Queue Overflow. Cannot enqueue " << data << endl;
            return;
        }

        // First enqueue initializes front to 0 (first valid index).
        if (front == -1) {
            front = 0;
        }

        rear++;
        queue_array[rear] = data;

        cout << "Enqueued: " << data << endl;
    }

    // ------------------------------------------------------------------------
    // dequeue(): remove from FRONT
    //
    // FIFO rule: elements leave from the front/beginning.
    // (Tutorialspoint, n.d.). [2](https://en.cppreference.com/w/cpp/language/namespace.html)
    //
    // Underflow:
    // - If empty, cannot dequeue -> print message + return -1 sentinel.
    // (GeeksforGeeks, 2025). [1](https://cplusplus.com/doc/tutorial/dynamic/)
    // ------------------------------------------------------------------------
    int dequeue() {
        if (isEmpty()) {
            cout << "Queue Underflow. Cannot dequeue from an empty queue." << endl;
            return -1; // sentinel
        }

        int dequeued_data = queue_array[front];
        front++;

        cout << "Dequeued: " << dequeued_data << endl;
        return dequeued_data;
    }

    // ------------------------------------------------------------------------
    // peek(): look at the front element without removing it
    //
    // This matches the typical queue "front" / "peek" operation:
    // - shows what will be dequeued next.
    // (ProgramGuru, n.d.). [3](https://intellipaat.com/blog/new-and-delete-operators-in-cpp/)
    //
    // If empty, prints message + returns sentinel (-1).
    // ------------------------------------------------------------------------
    int peek() const {
        if (isEmpty()) {
            cout << "Queue is empty. No front element." << endl;
            return -1;
        }
        return queue_array[front];
    }

    // ------------------------------------------------------------------------
    // display(): print elements from front to rear
    //
    // This visualizes FIFO order:
    // - front is next-out
    // - rear is most recent in
    // (Queue FIFO definition and operations). [1](https://cplusplus.com/doc/tutorial/dynamic/)[3](https://intellipaat.com/blog/new-and-delete-operators-in-cpp/)
    // ------------------------------------------------------------------------
    void display() const {
        if (isEmpty()) {
            cout << "Queue is empty." << endl;
            return;
        }

        cout << "Queue elements (front -> rear): ";
        for (int i = front; i <= rear; i++) {
            cout << queue_array[i] << " ";
        }
        cout << endl;
    }
};


// ============================================================================
// TEST HARNESS (main) — Demonstrates core queue behaviors
// ----------------------------------------------------------------------------
// Goal: show enqueue, dequeue, peek, display, and empty/full behaviors.
//
// NOTE about the limitation:
// If you keep enqueueing and dequeueing many times, you can hit overflow even
// when there are "gaps" at the beginning of the array (linear queue limitation).
// A circular queue fixes that. [1](https://cplusplus.com/doc/tutorial/dynamic/)[3](https://intellipaat.com/blog/new-and-delete-operators-in-cpp/)
// ============================================================================

int main() {
    SimpleQueue q;

    q.enqueue(10);
    q.enqueue(20);
    q.enqueue(30);
    q.enqueue(40);

    q.display();

    cout << "Peek (front): " << q.peek() << endl;

    q.dequeue();
    q.display();

    q.dequeue();
    q.display();

    q.enqueue(50);
    q.display();

    // Uncomment to demonstrate underflow:
    /*
    while (!q.isEmpty()) {
        q.dequeue();
    }
    q.dequeue(); // underflow example
    */

    return 0;
}


/*
===============================================================================
APA-STYLE REFERENCES (Linked)
-------------------------------------------------------------------------------
GeeksforGeeks. (2025, September 20). Queue using array – simple implementation.https://www.geeksforgeeks.org/dsa/array-implementation-of-queue-simple/ [1](https://cplusplus.com/doc/tutorial/dynamic/)

ProgramGuru. (n.d.). Queues – FIFO data structure.
https://programguru.org/programming/queues/ [3](https://intellipaat.com/blog/new-and-delete-operators-in-cpp/)

Tutorialspoint. (n.d.). Queue data structure (enqueue/dequeue, front/rear pointers).
https://www.tutorialspoint.com/data_structures_algorithms/dsa_queue.htm [2](https://en.cppreference.com/w/cpp/language/namespace.html)

Stack Overflow. (2024). What's the problem with "using namespace std;"?
https://stackoverflow.com/questions/1452721/whats-the-problem-with-using-namespace-std [4](https://stackoverflow.com/questions/4872373/why-is-including-using-namespace-into-a-header-file-a-bad-idea-in-c)
===============================================================================
*/