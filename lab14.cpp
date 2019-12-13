#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <stdexcept>
using namespace std;


void printBinary(int num){
    if(num == 0) return;
    printBinary(num/2);
    cout << num % 2;
}

bool isEvenBinary(int num){
    if(num == 0) return true;
    if(num%2 == 1) return !isEvenBinary(num/2);
    return isEvenBinary(num/2);
}

struct Node{
    Node(int data = 0,Node* next = nullptr):data(data),next(next){}
    int data;
    Node* next;
};

Node* SumofTwoList(Node* left, Node* right){
    //if empty,return empty list
    if(!left && !right) return nullptr;
    //if only right
    if(!left)
        return new Node(right->data,SumofTwoList(nullptr,right->next));
    //if only left
    if(!right)
        return new Node(left->data,SumofTwoList(left->next,nullptr));
    return new Node(left->data + right->data,SumofTwoList(left->next,right->next));
}

Node* ListConstruct(const vector<int>& v, int ind){
    if(ind == v.size()) return nullptr;
    return new Node(v[ind],ListConstruct(v,ind+1));
}

void printList(Node* headPtr){
    if(!headPtr) return;
    cout << headPtr->data;
    if(headPtr->next) cout << "->";
    printList(headPtr->next);
}

bool palindrome(char* start,int size){
    if(size < 2) return true;
    return palindrome(start+1,size-2) && *start == *(start + size-1);
}


struct TNode {
    TNode(int data = 0, TNode *left = nullptr, TNode *right = nullptr)
            : data(data), left(left), right(right) {}
    int data;
    TNode *left, *right;
};




int towers(int count, char start, char rest, char target){
    if(count < 2) return count;
    int result = towers(count-1,start,target,rest);
    result++;
    result += towers(count-1,rest,start,target);
    return result;
}


class MyException:public exception{
public:
    const char* what() const noexcept{
        return "The Tree is Empty";
    }
};

int Max(TNode* root) {
    if(!root) throw MyException();
    int result = root->data;
    if(root->left) result = max(result,Max(root->left));
    if(root->right) result = max(result,Max(root->right));
    return result;
}

int main() {

//    char s[] = "noon";
//    if (palindrome(s, 4)) { cout << "Yes!\n"; }
//
//    TNode a(1), b(2), c(4), d(8, &a, &b), e(16, &c), f(32, &d, &e);
//    cout << max(&f) << endl;
    try{
        cout << Max(nullptr);
    }catch(const exception& e){ cout << e.what();}
//    catch(MyException e){ cout << e.what();}

    int test = 1334;
//    printBinary(test);
//    cout << endl << isEvenBinary(test);
    Node* listone = ListConstruct({1,2,3,4},0);
//    printList(listone);
    cout << endl;
    Node* listTwo = ListConstruct({5,6,7},0);
//    printList(listTwo);
    cout << endl;
    Node* listThree = SumofTwoList(listone,listTwo);
    printList(listThree);

    cout << endl;
    for (int i = 1; i < 11; ++i) {
        cout << towers(i,'a','b','c') << " ";
    }

    cout << endl;
}