//
// Created by 刘禹辰 on 2019-11-21.
//

#include "Polynomial.h"
#include <iostream>
#include <vector>
#include "linked-list.cpp"
using namespace std;

void print_digit(ostream& os,int coeff, int index);

//polynomial implementation
ostream& operator<<(ostream& os, const Polynomial& rhs){
    if(rhs.degree != 0) {
        vector<int> temp;
        Node *cur = rhs.headptr;
        for (int k = 0; k < rhs.degree; ++k) {
            temp.push_back(cur->data);
            cur = cur->next;
        }
        // get the first element
        print_digit(os,temp.back(),rhs.degree-1);
        if(rhs.degree > 1) {
            for(size_t ind = rhs.degree - 1; ind != 0; --ind){
                int coeff = temp[ind - 1];
//                    if(coeff == 0) continue;
                if(coeff > 0) os << "+";
                print_digit(os,coeff,ind-1);
            }
        }
    }
    return os;
}

bool operator==(const Polynomial& lhs, const Polynomial& rhs){
    if(lhs.degree == rhs.degree){
        Node* cur1 = lhs.headptr;
        Node* cur2 = rhs.headptr;
        while(cur1){
            if(cur1->data != cur2->data) return false;
            cur1 = cur1->next;
            cur2 = cur2->next;
        }
        return true;
    }
    return false;
}

void Polynomial::clear_last_zero(){
    Node* last = listFindTail(headptr);
    while(last->data == 0) {
        Node* cur = headptr;
        Node* before;
        while (cur->next) {
            before = cur;
            cur = cur->next;
        }
        delete cur;
        before->next = nullptr;
        --degree;
        last = before;
    }
}

Polynomial::Polynomial():headptr(new Node(0)),degree(1){}

Polynomial::Polynomial(const vector<int>& input):headptr(new Node(input.back())),degree(input.size()){
    Node* cur = headptr;
    if(input.size() > 1)
        for(size_t ind = input.size() - 1; ind != 0; --ind){
            cur->next = new Node(input[ind - 1]);
            cur = cur->next;
        }
    clear_last_zero();
}

Polynomial::Polynomial(const Polynomial& rhs): headptr(new Node(rhs.headptr->data)),degree(rhs.degree){
    Node* cur = headptr;
    Node* cur2 = rhs.headptr->next;
    while(cur2){
        cur->next = new Node(cur2->data);
        cur = cur->next;
        cur2 = cur2->next;
    }
}

Polynomial& Polynomial::operator=(const Polynomial& rhs){
    if(this != &rhs){
        Node* cur = headptr;
        Node* cur2 = rhs.headptr;
        while(cur){
            delete cur;
            cur = cur->next;
        }
        headptr = new Node(cur2->data);
        cur = headptr;
        cur2 = cur2->next;
        while(cur2){
            cur->next = new Node(cur2->data);
            cur = cur->next;
            cur2 = cur2->next;
        }
        degree = rhs.degree;
    }
    return *this;
}

Polynomial::~Polynomial(){
    while(headptr){
        delete headptr;
        headptr = headptr -> next;
    }
}

Polynomial& Polynomial::operator+=(const Polynomial& rhs){
    Node* first = headptr;
    Node* second = rhs.headptr;
    Node* last = first;
    int digit;
    while(first && second){
        digit = first -> data + second -> data;
        first->data = digit;
        last = first;
        first = first->next;
        second = second -> next;
    }
    while(second){
        last -> next = new Node(second->data);
        last = last->next;
        second = second->next;
    }
    if(rhs.degree > degree) degree = rhs.degree;
    clear_last_zero();
    return *this;
}

int Polynomial::evaluate(int k) const{
    int result = headptr->data;
    Node* cur = headptr->next;
    while(cur){
        result += k*cur->data;
        k*=k;
        cur = cur->next;
    }
    return result;
}