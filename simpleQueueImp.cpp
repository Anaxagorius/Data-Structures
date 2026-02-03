#include <iostream>
using namespace std;

// STUDY NOTE: `using namespace std;`
// This is fine for small learning programs, but in larger projects it can
// cause name collisions (brings the entire std namespace into current scope).
// Many best-practice discussions recommend avoiding it at global scope.
// (Stack Overflow, 2024). [5](https://stackoverflow.com/questions/1452721/whats-the-problem-with-using-namespace-std)


// ============================================================================
// SimpleQueue (Array-Based, Fixed-Size Queue)
// ----------------------------------------------------------------------------
// BIG IDEA: A queue is FIFO (First-In, First-Out):
// - The first item enqueued is the first item dequeued.
// - Enqueue adds to the REAR (end).
// - Dequeue removes from the FRONT (beginning).
// (GeeksforGeeks, 2025; Tutorialspoint, n.d.). [1](https://www.geeksforgeeks.org/dsa/array-implementation-of-queue-simple/)[3](https://www.tutorialspoint.com/data_structures_algorithms/dsa_queue.htm)
//
// This implementation uses:
// - a fixed-size array: queue_array[MAX_SIZE]
// - integer indices: front and rear
//
// LIMITATION (Important Study Note):
// This is a *simple linear queue*, not a circular queue.
// That means once `rear` reaches MAX_SIZE - 1, the queue reports overflow,
// even if earlier elements have been dequeued (front moved forward).
// This can "waste" space at the beginning of the array.
// A circular queue fixes this by wrapping indices around.
// (GeeksforGeeks, 2025; ProgramGuru, n.d.). [1](https://www.geeksforgeeks.org/dsa/array-implementation-of-queue-simple/)[2](https://programguru.org/programming/queues/)
// ============================================================================

class SimpleQueue {
    static const int MAX_SIZE = 10;      // maximum capacity of queue (fixed-size)
    int queue_array[MAX_SIZE];           // storage for elements (array-based queue)
    int front;                           // index of the front element
    int rear;                            // index of the rear element

public:
    // ------------------------------------------------------------------------
    // Constructor: initialize empty queue state
    // Common convention for array queues:
    // - front = -1 and rear = -1 indicates "empty"
    // (Tutorialspoint describes queue usage with front/rear pointers). [3](https://www.tutorialspoint.com/data_structures_algorithms/dsa_queue.htm)
    // ------------------------------------------------------------------------
    SimpleQueue() {
        front = -1;
        rear = -1;
    }

    // ------------------------------------------------------------------------
    // Helper: check if the queue is "full" (overflow condition)
    //
    // In THIS simple design, we treat the queue as full when rear reaches
    // MAX_SIZE - 1 (end of array).
    //
    // STUDY NOTE: This is why space can be wasted:
    // even if front > 0 (we dequeued some items),
    // rear still might be stuck at the end.
    // (GeeksforGeeks, 2025). [1](https://www.geeksforgeeks.org/dsa/array-implementation-of-queue-simple/)
    // ------------------------------------------------------------------------
    bool isFull() const {
        return (rear == MAX_SIZE - 1);
    }

    // ------------------------------------------------------------------------
    // enqueue(data): add to REAR (end)
    //
    // FIFO rule: items join at the rear/end. (GeeksforGeeks, 2025). [1](https://www.geeksforgeeks.org/dsa/array-implementation-of-queue-simple/)
    //
    // Steps:
    // 1) If full -> overflow
    // 2) If first insert -> set front = 0
    // 3) Increment rear
    // 4) Store data at queue_array[rear]
    // ------------------------------------------------------------------------
    void enqueue(int data) {
        if (isFull()) {
            cout << "Queue Overflow. Cannot enqueue " << data << endl;
            return;
        }

        // If queue was empty, front is initialized on first enqueue.
        if (front == -1) {
            front = 0;
        }

        rear++;
        queue_array[rear] = data;

        cout << "Enqueued: " << data << endl;
    }

    // ------------------------------------------------------------------------
    // dequeue(): remove from FRONT (beginning)
    //
    // FIFO rule: items leave from the front/beginning. (Tutorialspoint, n.d.). [3](https://www.tutorialspoint.com/data_structures_algorithms/dsa_queue.htm)
    //
    // Underflow condition:
    // - If the queue is empty, we cannot dequeue.
    // - Here, emptiness is detected if:
    //     front == -1 OR front > rear
    //
    // IMPORTANT API NOTE:
    // Returning -1 is a "sentinel value" and can be unsafe if -1 is valid data.
    // Alternatives:
    // - throw an exception
    // - return bool and use an output parameter
    // - return std::optional<int> (modern approach)
    // (General overflow/underflow conditions are discussed in array-queue writeups). [1](https://www.geeksforgeeks.org/dsa/array-implementation-of-queue-simple/)
    // ------------------------------------------------------------------------
    int dequeue() {
        if (isEmpty()) {
            cout << "Queue Underflow. Cannot dequeue from an empty queue." << endl;
            return -1; // sentinel error value
        }

        int dequeued_data = queue_array[front];
        front++;

        cout << "Dequeued: " << dequeued_data << endl;
        return dequeued_data;
    }

    // ------------------------------------------------------------------------
    // isEmpty(): check empty state
    //
    // In this design, the queue is empty when:
    // - front == -1 (never enqueued), OR
    // - front > rear (we dequeued past last element)
    //
    // This matches the “front and rear pointer” style described in common
    // queue explanations. (Tutorialspoint, n.d.). [3](https://www.tutorialspoint.com/data_structures_algorithms/dsa_queue.htm)
    // ------------------------------------------------------------------------
    bool isEmpty() const {
        return (front == -1 || front > rear);
    }

    // ------------------------------------------------------------------------
    // peek(): view the front element without removing it
    //
    // This is the "Front" operation in queue ADT: inspect what will be removed next
    // (FIFO: next-out is at the front). (ProgramGuru, n.d.). [2](https://programguru.org/programming/queues/)
    //
    // Same sentinel risk applies if queue is empty.
    // ------------------------------------------------------------------------
    int peek() const {
        if (isEmpty()) {
            cout << "Queue is empty. No front element." << endl;
            return -1; // sentinel
        }
        return queue_array[front];
    }

    // ------------------------------------------------------------------------
    // display(): print queue elements from front to rear
    //
    // This helps visualize FIFO order:
    // - front is the next element to be dequeued
    // - rear is the most recently enqueued element
    // (FIFO definition: first inserted removed first). [1](https://www.geeksforgeeks.org/dsa/array-implementation-of-queue-simple/)[2](https://programguru.org/programming/queues/)
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
// Optional: quick test harness (uncomment to run)
// ----------------------------------------------------------------------------
// This shows:
// - Enqueue until overflow
// - Dequeue until underflow
// - peek() usage
// ============================================================================
/*
int main() {
    SimpleQueue q;

    q.enqueue(10);
    q.enqueue(20);
    q.enqueue(30);
    q.display();

    cout << "Peek (front): " << q.peek() << endl;

    q.dequeue();
    q.display();

    // Fill up queue
    for (int i = 40; i <= 120; i += 10) {
        q.enqueue(i);
    }
    q.display();

    // Dequeue everything
    while (!q.isEmpty()) {
        q.dequeue();
    }

    // Underflow example
    q.dequeue();

    return 0;
}
*/


/*
===============================================================================
APA-STYLE REFERENCES (Linked)
-------------------------------------------------------------------------------
GeeksforGeeks. (2025, September 20). Queue using array – simple implementation.
[1](https://www.geeksforgeeks.org/dsa/array-implementation-of-queue-simple/)

ProgramGuru. (n.d.). Queues – FIFO data structure.
[2](https://programguru.org/programming/queues/)

Tutorialspoint. (n.d.). Queue data structure (enqueue/dequeue, front/rear pointers).
[3](https://www.tutorialspoint.com/data_structures_algorithms/dsa_queue.htm)

Stack Overflow. (2024). What’s the problem with “using namespace std;”?
[5](https://stackoverflow.com/questions/1452721/whats-the-problem-with-using-namespace-std)
===============================================================================
*/