/*
  Linked list base: the Node type as struct
  Section D
  19F
 */
#include <iostream>
using namespace std;

struct Node {
    Node(int data = 0, Node* next = nullptr) : data(data), next(next) {}
    int data;
    Node* next;
};

void listDisplay(Node* headPtr) {
//void listDisplay(const Node* headPtr) {
    Node* p = headPtr;
    //    while (headPtr->next != nullptr) {
    while (p != nullptr) {
        cout << p->data << ' ';
        p = p->next; // bump
    }
    cout << endl;
}

Node* listFindTail(Node* headPtr) {
    if (headPtr == nullptr) return nullptr;
    Node* p = headPtr;
    while (p->next != nullptr) {
        p = p->next; // bump
    }
    return p;
}

//void listInsertTail(Node* headPtr, int data) {
void listInsertTail(Node*& headPtr, int data) {
    if (headPtr == nullptr) {
        headPtr = new Node(data);
    }
    else {
        Node* last = listFindTail(headPtr);
        // Node* tmp = new Node(data);
        // last->next = tmp;
        last->next = new Node(data);
    }
}

//void listInsertHead(Node* headPtr, int data) {
void listInsertHead(Node*& headPtr, int data) {
    // // 1. Create a node for the data
    // Node* nodeToInsert = new Node(data);
    // // 2. Make the new node point to the old head node
    // nodeToInsert->next = headPtr;
    // Node* nodeToInsert = new Node(data, headPtr);
    // // 3. Make the head be the new node
    // headPtr = nodeToInsert;
    headPtr = new Node(data, headPtr);
}

//void listInsert(Node* prior, Node* after, int data) {
void listInsert(Node* prior, int data) {
    // Node* nodeToInsert = new Node(data, after);
    // prior->next = nodeToInsert;
    // Node* after = prior->next;
    // prior->next = new Node(data, after);
    prior->next = new Node(data, prior->next);
}

void listHeadRemove(Node*& headPtr) {
    if (headPtr != nullptr) {
        Node* victim = headPtr;
        headPtr = headPtr->next;
        //delete headPtr;
        delete victim;
    }
}

Node* listDuplicate(Node* headPtr) {
    if (headPtr == nullptr) return nullptr;
    Node* p = headPtr->next;
    Node* result = new Node(headPtr->data);
    Node* last = result;

    while (p != nullptr) {
        last->next = new Node(p->data);
        p = p->next;
        last = last->next;
    }
    return result;
}

