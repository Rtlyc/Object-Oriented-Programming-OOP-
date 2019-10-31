//
// Created by 刘禹辰 on 2019-10-30.
//

#include "Noble.h"
#include <iostream>
#include <string>
#include <vector>
#include "Protector.h"
using namespace std;

namespace WarriorCraft {

//Protector Implementation

    Protector::Protector(const string &name, double strength) : name(name), strength(strength) {}

    void Protector::defend(double amount) {
        strength *= (1 - amount);
        if (strength <= 0) {
            strength = 0;
            isDead = true;
        }
    };

    const string &Protector::getName() const { return name; }

    Noble *Protector::getNoble() const { return mynoble; }

    Noble *&Protector::getNoble() { return mynoble; }

    double Protector::getStrength() const { return strength; }

    bool Protector::isAlive() const { return !isDead; }

//Wizard Implementation

    void Wizard::defend(double amount) {
        Protector::defend(amount);
        cout << "POOF!" << endl;
    }


//Warrior Implementation

    void Warrior::defend(double amount) {
        Protector::defend(amount);
        cout << getName() << " says: Take that in the name of my lord, " << getNoble()->getName() << endl;
    }

//Archer Implementation

    void Archer::defend(double amount) {
        cout << "TWANG! ";
        Warrior::defend(amount);
    }


//Swordsman Implementation
    void Swordsman::defend(double amount) {
        cout << "CLANG! ";
        Warrior::defend(amount);
    }
}
