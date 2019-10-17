//
// Created by 刘禹辰 on 2019-10-16.
//

#ifndef HW6_WARRIOR_H
#define HW6_WARRIOR_H


#include <string>
#include <iostream>
#include "Noble.h"

class Noble;
class Warrior{
    friend std::ostream&operator<<(std::ostream& os,const Warrior& awarrior);

    friend bool Noble::fire(Warrior &awarrior);
    friend bool Noble::hire(Warrior &awarrior);


public:
    Warrior(const std::string& name,int strength);
    double getStrength() const;
    const std::string& getName() const;
    Noble* getNoble() const;
    void losestrength(double k);

    bool runaway();
private:
    double strength;
    std::string warriorname;
    Noble* mynoble = nullptr;
};

#endif //HW6_WARRIOR_H
