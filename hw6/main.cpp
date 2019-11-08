#include "Noble.h"
#include "Warrior.h"
#include <iostream>
#include <vector>
#include <string>
using namespace std;
//using namespace WarriorCraft;



// Your Noble and Warrior classes should go here.




ostream&operator<<(ostream& os,const Noble& anoble);
ostream&operator<<(ostream& os,const Warrior& awarrior);



int main() {
    Noble art("King Arthur");
    Noble lance("Lancelot du Lac");
    Noble jim("Jim");
    Noble linus("Linus Torvalds");
    Noble billie("Bill Gates");

    Warrior cheetah("Tarzan", 10);
    Warrior wizard("Merlin", 15);
    Warrior theGovernator("Conan", 12);
    Warrior nimoy("Spock", 15);
    Warrior lawless("Xena", 20);
    Warrior mrGreen("Hulk", 8);
    Warrior dylan("Hercules", 3);

    jim.hire(nimoy);
    lance.hire(theGovernator);
    art.hire(wizard);
    lance.hire(dylan);
    linus.hire(lawless);
    billie.hire(mrGreen);
    art.hire(cheetah);

    cout << jim << endl;
    cout << lance << endl;
    cout << art << endl;
    cout << linus << endl;
    cout << billie << endl;

    cheetah.runaway();
    cout << art << endl;

    art.battle(lance);
    jim.battle(lance);
    linus.battle(billie);
    billie.battle(lance);
}

ostream&operator<<(ostream& os,const Warrior& awarrior){
    os << awarrior.warriorname << ": " << awarrior.strength << endl;
    return os;
};
ostream&operator<<(ostream& os,const Noble& anoble){
    os << anoble.noblename << " has an army of " << anoble.allwarriors.size() << endl;
    for(const Warrior* awarrior:anoble.allwarriors){
        cout << "    " << *awarrior;
    }
    return os;
}


