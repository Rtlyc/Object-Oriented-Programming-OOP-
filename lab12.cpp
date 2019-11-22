#include <iostream>
#include <vector>
using namespace std;



class DoublyLinkedList{
    struct Node{
        int data;
        Node* prev;
        Node* next;

        Node(int k, Node* prev = nullptr, Node* next = nullptr): data(k),prev(prev),next(next){}
    };

public:
    DoublyLinkedList():head(new Node(0)),trailer(new Node(0)),Size(0){
        head->next = trailer;
        trailer->prev = head;
    }
    DoublyLinkedList(const vector<int>& v): head(new Node(0)), trailer(new Node(0)),Size(v.size()){
        Node* cur = head;
        for(int k: v){
            cur->next = new Node(k,cur,nullptr);
            cur = cur->next;
        }
        cur->next = trailer;
        trailer->prev = cur;
    }

    void display() const{
        Node* cur = head->next;
        while(cur->next){
            cout << cur->data << " ";
            cur = cur->next;
        }
    }

    void push_back(int k){
        Node* last = new Node(k,trailer->prev,trailer);
        trailer->prev->next = last;
        trailer->prev = last;
        Size++;
    }

    int front() const{
        return head->next->data;
    }

    int& front(){
        return head->next->data;
    }

    int back() const{
        return trailer->prev->data;
    }

    int& back(){
        return trailer->prev->data;
    }

    int size() const{
        return Size;
    }

    void push_front(int k){
        Node* temp = new Node(k,head,head->next);
        head->next->prev = temp;
        head->next = temp;
        Size++;
    }

    int pop_front(){
        if(!Size) return -1;
        Node* temp = head->next;
        int result = temp->data;
        head->next = temp->next;
        head->next->prev = head;
        --Size;
        delete temp;
        return result;
    }

    int pop_back(){
        if(!Size) return -1;
        Node* temp = trailer->prev;
        int result = temp->data;
        temp->prev->next = trailer;
        trailer->prev = temp->prev;
        delete temp;
        --Size;
        return result;
    }

    void clear(){
        Node* cur = head->next;
        while(cur->next){
            Node* after = cur->next;
            delete cur;
            cur = after;
        }
        trailer->prev = head;
        head->next = trailer;
        Size = 0;
    }

    int operator[](int ind) const{
        int count = 0;
        Node* cur = head->next;
        while(count != ind){
            cur = cur->next;
            count++;
        }
        return cur->data;
    }

    int& operator[](int ind){
        int count = 0;
        Node* cur = head->next;
        while(count != ind){
            cur = cur->next;
            count ++;
        }
        return cur->data;
    }

    friend ostream& operator<<(ostream& os, const DoublyLinkedList& rhs){
        Node* cur = rhs.head->next;
        while(cur->next){
            cout << cur->data << " ";
            cur = cur->next;
        }
        return os;
    }

public:
    class Iterator{
        friend DoublyLinkedList;
    public:
        Iterator(Node* ptr): valPtr(ptr){}
        Iterator& operator++(){
            valPtr = valPtr->next;
            return *this;
        }
        Iterator& operator--(){
            valPtr = valPtr->prev;
            return *this;
        }
        bool operator==(const Iterator& other)const{
            return valPtr == other.valPtr;
        }
        bool operator!=(const Iterator& other)const{
            return !(*this == other);
        }
        int& operator*(){
            return valPtr->data;
        }

    private:
        Node* valPtr;
    };

    Iterator begin() const{
        return Iterator{head->next};
    }

    Iterator end() const{
        return Iterator{trailer};
    }

    Iterator insert(Iterator cur, int k){
        Node* temp = new Node(k,cur.valPtr->prev,cur.valPtr);
        cur.valPtr->prev->next = temp;
        cur.valPtr->prev = temp;
        Size++;
        return --cur;
    }

    Iterator erase(Iterator cur){
        Node* pre = cur.valPtr->prev;
        Node* after = cur.valPtr->next;
        pre->next = after;
        after->prev = pre;
        Size--;
        delete cur.valPtr;
        return Iterator(after);
    }

    DoublyLinkedList(const DoublyLinkedList& rhs):head(new Node(0)),trailer(new Node(0)), Size(rhs.Size){
        Node* cur1 = head;
        Node* cur2 = rhs.head->next;
        while(cur2->next){
            cur1->next = new Node(cur2->data,cur1,nullptr);
            cur2 = cur2->next;
            cur1 = cur1->next;
        }
        cur1->next = trailer;
        trailer->prev = cur1;
    }

    DoublyLinkedList& operator=(const DoublyLinkedList& rhs){
        if(&rhs == this) return *this;
        clear();
        Node* cur1 = head;
        Node* cur2 = rhs.head->next;
        while(cur2->next){
            cur1->next = new Node(cur2->data,cur1,nullptr);
            cur1 = cur1->next;
            cur2 = cur2->next;
        }
        cur1->next = trailer;
        trailer->prev = cur1;
        Size = rhs.size();
        cout << "List::op=(List)" << endl;
        return *this;
    }

    ~DoublyLinkedList(){
        clear();
        delete head;
        delete trailer;
        cout << "~List()" << endl;
    }


private:
    Node* head;
    Node* trailer;
    int Size;
};




// Task 1
void printListInfo(const DoublyLinkedList& myList) {
    cout << "size: " << myList.size()
         << ", front: " << myList.front()
         << ", back(): " << myList.back()
         << ", list: " << myList << endl;
}

// The following should not compile. Check that it does not.
// void changeFrontAndBackConst(const List& theList){
//     theList.front() = 17;
//     theList.back() = 42;
// }

void changeFrontAndBack(DoublyLinkedList& theList){
    theList.front() = 17;
    theList.back() = 42;
}

// Task 4
void printListSlow(const DoublyLinkedList& myList) {
    for (size_t i = 0; i < myList.size(); ++i) {
        cout << myList[i] << ' ';
    }
    cout << endl;
}

// Task 8
void doNothing(DoublyLinkedList aList) {
    cout << "In doNothing\n";
    printListInfo(aList);
    cout << endl;
    cout << "Leaving doNothing\n";
}

int main() {

    // Task 1
    cout << "\n------Task One------\n";
    DoublyLinkedList myList;
    cout << "Fill empty list with push_back: i*i for i from 0 to 9\n";
    for (int i = 0; i < 10; ++i) {
        cout << "myList.push_back(" << i*i << ");\n";
        myList.push_back(i*i);
        printListInfo(myList);
    }
    cout << "===================\n";

    cout << "Modify the first and last items, and display the results\n";
    changeFrontAndBack(myList);
    printListInfo(myList);
    cout << "===================\n";

    cout << "Remove the items with pop_back\n";
    while (myList.size()) {
        printListInfo(myList);
        myList.pop_back();
    }
    cout << "===================\n";

    // Task 2
    cout << "\n------Task Two------\n";
    cout << "Fill empty list with push_front: i*i for i from 0 to 9\n";
    for (int i = 0; i < 10; ++i) {
        cout << "myList2.push_front(" << i*i << ");\n";
        myList.push_front(i*i);
        printListInfo(myList);
    }
    cout << "===================\n";
    cout << "Remove the items with pop_front\n";
    while (myList.size()) {
        printListInfo(myList);
        myList.pop_front();
    }
    cout << "===================\n";

    // Task 3
    cout << "\n------Task Three------\n";
    cout << "Fill empty list with push_back: i*i for i from 0 to 9\n";
    for (int i = 0; i < 10; ++i) {
        myList.push_back(i*i);
    }
    printListInfo(myList);
    cout << "Now clear\n";
    myList.clear();
    cout << "Size: " << myList.size() << ", list: " << myList << endl;
    cout << "===================\n";

    // Task 4
    cout << "\n------Task Four------\n";
    cout << "Fill empty list with push_back: i*i for i from 0 to 9\n";
    for (int i = 0; i < 10; ++i)  myList.push_back(i*i);
    cout << "Display elements with op[]\n";
    for (size_t i = 0; i < myList.size(); ++i) cout << myList[i] << ' ';
    cout << endl;
    cout << "Add one to each element with op[]\n";
    for (size_t i = 0; i < myList.size(); ++i) myList[i] += 1;
    cout << "And print it out again with op[]\n";
    for (size_t i = 0; i < myList.size(); ++i) cout << myList[i] << ' ';
    cout << endl;
    cout << "Now calling a function, printListSlow, to do the same thing\n";
    printListSlow(myList);
    cout << "Finally, for this task, using the index operator to modify\n"
         << "the data in the third item in the list\n"
         << "and then using printListSlow to display it again\n";
    myList[2] = 42;
    printListSlow(myList);


    // Task 5
    cout << "\n------Task Five------\n";
    cout << "Fill empty list with push_back: i*i for i from 0 to 9\n";
    myList.clear();
    for (int i = 0; i < 10; ++i)  myList.push_back(i*i);
    printListInfo(myList);
    cout << "Now display the elements in a ranged for\n";
    for (int x : myList) cout << x << ' ';
    cout << endl;
    cout << "And again using the iterator type directly:\n";
    // Note you can choose to nest the iterator class or not, your choice.
    //for (iterator iter = myList.begin(); iter != myList.end(); ++iter) {
    for (DoublyLinkedList::Iterator iter = myList.begin(); iter != myList.end(); ++iter) {
        cout << *iter << ' ';
    }
    cout << endl;
    cout << "WOW!!! (I thought it was cool.)\n";

    // Task 6
    cout << "\n------Task Six------\n";
    cout << "Filling an empty list with insert at end: i*i for i from 0 to 9\n";
    myList.clear();
    for (int i = 0; i < 10; ++i) myList.insert(myList.end(), i*i);
    printListInfo(myList);
    cout << "Filling an empty list with insert at begin(): "
         << "i*i for i from 0 to 9\n";
    myList.clear();
    for (int i = 0; i < 10; ++i) myList.insert(myList.begin(), i*i);
    printListInfo(myList);
    // ***Need test for insert other than begin/end***
    cout << "===================\n";

    // Task 7
    cout << "\n------Task Seven------\n";
    cout << "Filling an empty list with insert at end: i*i for i from 0 to 9\n";
    myList.clear();
    for (int i = 0; i < 10; ++i) myList.insert(myList.end(), i*i);
    cout << "Erasing the elements in the list, starting from the beginning\n";
    while (myList.size()) {
        printListInfo(myList);
        myList.erase(myList.begin());
    }
    // ***Need test for erase other than begin/end***
    cout << "===================\n";

    // Task 8
    cout << "\n------Task Eight------\n";
    cout << "Copy control\n";
    cout << "Filling an empty list with insert at end: i*i for i from 0 to 9\n";
    myList.clear();
    for (int i = 0; i < 10; ++i) myList.insert(myList.end(), i*i);
    printListInfo(myList);
    cout << "Calling doNothing(myList)\n";
    doNothing(myList);
    cout << "Back from doNothing(myList)\n";
    printListInfo(myList);

    cout << "Filling listTwo with insert at begin: i*i for i from 0 to 9\n";
    DoublyLinkedList listTwo;
    for (int i = 0; i < 10; ++i) listTwo.insert(listTwo.begin(), i*i);
    printListInfo(listTwo);
    cout << "listTwo = myList\n";
    listTwo = myList;
    cout << "myList: ";
    printListInfo(myList);
    cout << "listTwo: ";
    printListInfo(listTwo);
    cout << "===================\n";
}
