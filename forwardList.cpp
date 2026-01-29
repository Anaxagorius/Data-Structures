
#include <iostream>
#include <forward_list>   // Library for inbuilt singly linked list in STL

int main() {

    // Create an empty forward_list of integers named demolist
    std::forward_list<int> demolist;
    // Remember: forward_list is a singly linked list with only forward iterators.

    // Insert elements at the front of the list
    demolist.push_front(10);
    demolist.push_front(20);
    demolist.push_front(30);
    demolist.push_front(40);

    // Display the demolist using an iterator
    std::cout << "Demolist: ";
    for (auto it = demolist.begin(); it != demolist.end(); ++it) {
        std::cout << *it << " ";   // Dereference iterator to get the value
    }
    std::cout << std::endl;

    // Remove the front element
    demolist.pop_front();

    // Display the demolist after popping the front element
    std::cout << "After pop_front: ";
    for (auto it = demolist.begin(); it != demolist.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    return 0;
}
