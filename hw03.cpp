/*
 * Yuchen Liu
 * yl5680
 * CS2124
 * September 29th, 2019
 */


#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

class Warrior{
    friend ostream& operator<<(ostream& os,const Warrior& awarrior){
        os << "Warrior: " << awarrior.warriorname << ", weapon: "
        << awarrior.aweapon;
        return os;
    };
    class Weapon{
        friend ostream& operator<<(ostream& os, const Weapon& weapon){
            os << weapon.weaponname << ", " << weapon.strength;
            return os;
        }
    public:
        Weapon(const string& name,int strength):weaponname(name),strength(strength){}
        void reduce(int damage){strength -= damage;};
        int getStrength()const{return strength;};
    private:
        string weaponname;
        int strength;
    };

public:
    Warrior(const string& warrior,const string& weapon, int strength):
    warriorname(warrior),aweapon(weapon,strength){}
    const string& getName() const;
    void battle(Warrior& rival);
    Weapon& getWeapon(){
        return aweapon;
    };
private:
    string warriorname;
    Weapon aweapon;
};

void display(const vector<Warrior>& allwarriors); // show status
size_t findWarrior(const string& name, const vector<Warrior>& allwarriors); // locate warriors by index



int main() {
    string command;
    ifstream ifs("warriors.txt");
    vector<Warrior> allwarriors;
    while(ifs >> command){
        if(command == "Warrior"){
            string warrior,weapon;
            int strength;
            ifs >> warrior >> weapon >> strength;
            allwarriors.emplace_back(warrior,weapon,strength);
        }else if(command == "Status"){
            display(allwarriors);
        }else if(command == "Battle"){
            string name1,name2;
            ifs >> name1 >> name2;
            Warrior& warrior1 = allwarriors[findWarrior(name1,allwarriors)];
            Warrior& warrior2 = allwarriors[findWarrior(name2,allwarriors)];
            warrior1.battle(warrior2);
        }
    }
    ifs.close();
    return 0;
}

size_t findWarrior(const string& name, const vector<Warrior>& allwarriors){
    for(size_t index = 0; index < allwarriors.size(); index++){
        if(allwarriors[index].getName() == name){
            return index;
        }
    }
    return allwarriors.size();
}

void Warrior::battle(Warrior &rival) {
    Weapon& bweapon = rival.getWeapon();
    cout << warriorname << " battles " << rival.getName() << endl;
    if(aweapon.getStrength() == 0){
        if(bweapon.getStrength() == 0){
            cout << "Oh, NO! They're both dead! Yuck!" << endl;
        }else if(bweapon.getStrength() > 0){
            cout << "He's dead, " << rival.warriorname << endl;
        }
    }else if(aweapon.getStrength() > 0){
        if(bweapon.getStrength() == 0){
            cout << "He's dead, " << warriorname << endl;
        }else if(aweapon.getStrength() == bweapon.getStrength()){
            int damage = aweapon.getStrength();
            aweapon.reduce(damage);
            bweapon.reduce(damage);
            cout << "Mutual Annihilation: " << warriorname << " and "
            << rival.warriorname << " die at each other's hands" << endl;
        }else if(aweapon.getStrength() > bweapon.getStrength()){
            aweapon.reduce(bweapon.getStrength());
            bweapon.reduce(bweapon.getStrength());
            cout << warriorname << " defeats " << rival.getName() << endl;
        } else{
            bweapon.reduce(aweapon.getStrength());
            aweapon.reduce(aweapon.getStrength());
            cout << rival.getName() << " defeats " << warriorname << endl;
        }
    }
}

const string& Warrior::getName()const{
    return warriorname;
}

void display(const vector<Warrior>& allwarriors){
    cout << "There are: " << allwarriors.size() << " warriors" << endl;
    for(const Warrior& awarrior:allwarriors){
        cout << awarrior << endl;
    }
}
