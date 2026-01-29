#include <iostream>

using namespace std;
//Linked list node structure

class Node {//Node class that has two members: an integer data and a pointer to the next node
public://
    int data;//
    Node* next;

    Node(int val) {//Constructor to initialize the node with a value and set next to nullptr
        data = val;
        next = nullptr;
    }
};

int main() {
    //Creating nodes
    Node* nodeHead = new Node(10);  // Initialize head with a value
    Node* nodeA = new Node(20);
    Node* nodeB = new Node(30);
    Node* nodeC = new Node(40);
    Node* nodeD = new Node(50);

    //Linking nodes
    nodeHead->next = nodeA;
    nodeA->next = nodeB;
    nodeB->next = nodeC;
    nodeC->next = nodeD;

    printf("Linked List: ");
   

    return 0;
}