//
// Created by 刘禹辰 on 2019-10-16.
//

#include "Warrior.h"
#include <vector>
#include <iostream>
#include <string>
#include "Noble.h"

using namespace std;
class Noble;

// Warrior implementation
bool Warrior::runaway(){
    if (!mynoble) return false;
    mynoble -> deletewarrior(this);
    mynoble = nullptr;
    return true;
}
Warrior::Warrior(const string& name,int strength):warriorname(name),strength(strength){}
double Warrior::getStrength() const{return strength;}
const string& Warrior::getName() const{return warriorname;}
Noble* Warrior::getNoble() const{return mynoble;}
void Warrior::losestrength(double k){strength *=(1-k);}

