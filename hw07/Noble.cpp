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
// Noble Implementation

    Noble::Noble(const string &name, double strength) : name(name), strength(strength) {}

    void Noble::battle(Noble &other) {
        cout << name << " battles " << other.name << endl;
//
//        cout << name << " : " << strength;
//        cout << "   " << other.name << "\t:" << other.strength << endl;
        if (!(isAlive()) && !other.isAlive()) {
            cout << "Oh, NO!  They're both dead!  Yuck!" << endl;
            return;
        }
        if (!(isAlive())) {
            cout << "He is dead, " << other.getName() << endl;
            return;
        }
        if (!other.isAlive()) {
            cout << "He is dead, " << getName() << endl;
            return;
        }
        double left = strength;
        double right = other.strength;
        if (left != 0) {
            fightback(right / left);
        } else isDead = true;
        if (right != 0) {
            other.fightback(left / right);
        } else other.isDead = true;
        if (left == right) {
            cout << "Oh, NO!  They're both dead!  Yuck!" << endl;
        } else if (left > right) {
            cout << name << " defeats " << other.name << endl;
        } else {
            cout << other.name << " defeats " << name << endl;
        }
    };

    const string &Noble::getName() const { return name; }

    bool Noble::isAlive() const { return !isDead; }

    void Noble::fightback(double amount) {
        strength *= (1 - amount);
        if (strength <= 0) {
            strength = 0;
            isDead = true;
        }
    }

    double Noble::getStrength() const { return strength; }

    double &Noble::getStrength() { return strength; }


// Lord Implementation
    Lord::Lord(const string &name) : Noble(name) {}

    bool Lord::hires(Protector &other) {
        if (!(other.isAlive() && isAlive())) return false;
        if (other.getNoble()) return false;
        other.getNoble() = this;
        getStrength() += other.getStrength();
        allprotectors.push_back(&other);
        return true;
    }

    bool Lord::fires(Protector &other) {
        size_t ind = find(other);
        if (ind == allprotectors.size()) return false;
        for (size_t j = ind; j < allprotectors.size() - 1; j++) {
            allprotectors[j] = allprotectors[j + 1];
        }
        allprotectors.pop_back();
        getStrength() -= other.getStrength();
        other.getNoble() = nullptr;
        return true;
    }

    void Lord::fightback(double amount) {
        Noble::fightback(amount);
        for (size_t ind = 0; ind < allprotectors.size(); ++ind) {
            allprotectors[ind]->defend(amount);
        }
    }

    size_t Lord::find(const Protector &other) const {
        for (size_t ind = 0; ind < allprotectors.size(); ++ind) {
            if (allprotectors[ind] == &other) return ind;
        }
        return allprotectors.size();
    }


// PersonWithStrengthToFight Implementation

    PersonWithStrengthToFight::PersonWithStrengthToFight(const string &name, double strength) : Noble(name, strength) {}
}