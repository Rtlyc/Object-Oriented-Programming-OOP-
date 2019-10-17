//
// Created by 刘禹辰 on 2019-10-16.
//

#include <string>
#include <ostream>
#include "Warrior.h"

using namespace std;

class Warrior;
// Noble implementation
Noble::Noble(const string& name):noblename(name){};

void Noble::modify(double amount){
    for(Warrior* w:allwarriors){
        w->losestrength(amount);
    }
}
bool Noble::battle(Noble& othernoble){
    cout << noblename << " battles " << othernoble.noblename << endl;
    if(!alive){
        if (othernoble.alive){
            cout << noblename << " is dead already" << endl;
            return false;
        }else{
            cout << "Oh, NO!  They're both dead!  Yuck!" << endl;
            return false;
        }
    }
    if(!othernoble.alive){
        cout << "He's dead, " << noblename << endl;
    }else{
        if(totalstrength == othernoble.totalstrength){
            totalstrength = 0;
            othernoble.totalstrength = 0;
            alive = false;
            othernoble.alive = false;
            modify(1);
            othernoble.modify(1);
            cout << "Mutual Annihalation: " << noblename << " and "
                 << othernoble.noblename << " die at each other's hands" << endl;
        }else if(totalstrength > othernoble.totalstrength){
            othernoble.modify(1);
            othernoble.alive = false;
            modify(othernoble.totalstrength/totalstrength);
            othernoble.totalstrength = 0;
            cout << noblename << " defeats " << othernoble.noblename << endl;
        }else if(totalstrength < othernoble.totalstrength){
            modify(1);
            alive = false;
            othernoble.modify(totalstrength/othernoble.totalstrength);
            totalstrength = 0;
            cout << othernoble.noblename << " defeats " << noblename << endl;
        }
    }
    return true;
}

bool Noble::fire(Warrior& awarrior){
    if (awarrior.getNoble() == this){
        for (size_t index = 0;index<allwarriors.size();++index){
            if (allwarriors[index] == &awarrior){
                allwarriors[index] = allwarriors.back();
                allwarriors.pop_back();
                break;
            }
        }
        awarrior.mynoble= nullptr;
        totalstrength -= awarrior.getStrength();
        cout << "You don't work for me anymore " << awarrior.getName()
             << "! -- " << noblename << endl;
        return true;
    }
    return false;
}
bool Noble::hire(Warrior& awarrior){
    if(awarrior.getNoble()!=nullptr || !alive){
        return false;
    }else{
        awarrior.mynoble = this;
        allwarriors.push_back(&awarrior);
        totalstrength += awarrior.getStrength();
        return true;
    }
}

void Noble::deletewarrior(Warrior* awarrior){
    for(size_t index = 0; index < allwarriors.size(); ++index){
        if (awarrior == allwarriors[index]){
            cout << awarrior -> getName() << " flees in terror, abandoning his lord, " << noblename << endl;
            totalstrength -= awarrior->getStrength();
            allwarriors[index] = allwarriors.back();
            allwarriors.pop_back();
        }
    }
}

