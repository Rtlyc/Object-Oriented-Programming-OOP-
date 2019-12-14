//
// Created by 刘禹辰 on 2019-11-21.
//

#include <iostream>
#include <vector>

#ifndef HW08_POLYNOMIAL_H
#define HW08_POLYNOMIAL_H

struct Node;

class Polynomial{
    friend std::ostream& operator<<(std::ostream& os, const Polynomial& rhs);

    friend bool operator==(const Polynomial& lhs, const Polynomial& rhs);

    void clear_last_zero();

public:
    // Polynomial p();
    // Polynomial p({})
    Polynomial();
    Polynomial(const std::vector<int>& input);

//    copy control
    Polynomial(const Polynomial& rhs);

    Polynomial& operator=(const Polynomial& rhs);

    ~Polynomial();

    // +=
    Polynomial& operator+=(const Polynomial& rhs);

    int evaluate(int k) const;

private:
    Node* headptr;
    int degree;
};


#endif //HW08_POLYNOMIAL_H
