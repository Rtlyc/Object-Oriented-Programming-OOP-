//
// Created by 刘禹辰 on 2019-10-16.
//

#ifndef HW6_NOBLE_H
#define HW6_NOBLE_H

#include <string>
#include <vector>
#include <iostream>
//#include "Warrior.h"

class Warrior;
class Noble{
    friend std::ostream&operator<<(std::ostream& os,const Noble& anoble);
public:
    Noble(const std::string& name);
    bool battle(Noble& anoble);
    void modify(double amount);

    bool hire(Warrior& awarrior);
    bool fire(Warrior& awarrior);

    void deletewarrior(Warrior* awarrior);

private:
    std::string noblename;
    double totalstrength = 0;
    bool alive = true;
    std::vector<Warrior*> allwarriors;
};

#endif //HW6_NOBLE_H
