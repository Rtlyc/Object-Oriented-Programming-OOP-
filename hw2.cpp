/*
 * Yuchen Liu
 * yl5680
 * CS-2124 OOP
 * September 22, 2019
 * Homework 2
 */

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

struct Warrior{
    string name;
    int strength;
};

void readfile(ifstream& ifs);// open the file
void create_warriors(ifstream& file, vector<Warrior>& allwarriors);// save the warrior
void display(const vector<Warrior>& allwarriors);// display the strength of each warrior
Warrior& nametowarrior(const string& name, vector<Warrior>& allwarriors); // find warrior by name
void battle(ifstream& file, vector<Warrior>& allwarriors); // start battle

int main() {
    ifstream file;
    vector<Warrior> allwarriors;
    string order;
    readfile(file);
    while(file >> order){
        if (order == "Warrior"){
            create_warriors(file,allwarriors);
        }else if(order == "Status"){
            display(allwarriors);
        }else if(order == "Battle"){
            battle(file,allwarriors);
        }
    }
    file.close();
    return 0;
}

// open the file
void readfile(ifstream& ifs){
    if (!ifs){
        cerr << "Couldn't open the file!" << endl;
    }
    ifs.open("warriors.txt");
}

void create_warriors(ifstream& file, vector<Warrior>& allwarriors){
    string name;
    int strength;
    file >> name >> strength;
    allwarriors.push_back(Warrior{name,strength});
}

// display the number of the warriors
// display the strength of each warrior
void display(const vector<Warrior>& allwarriors){
    cout << "There are: " << allwarriors.size() << " Warriors" << endl;
    for(const Warrior& person: allwarriors){
        cout << "Warrior: " << person.name <<", strength: " << person.strength << endl;
    }
}

//finds the warrior in the list from the name in the file
Warrior& nametowarrior(const string& name, vector<Warrior>& allwarriors){
    for (Warrior& fighter: allwarriors){
        if (fighter.name == name){
            return fighter;
        }
    }
}


void battle(ifstream& file, vector<Warrior>& allwarriors){
    string name1, name2;
    file >> name1 >> name2;
    cout << name1 << " battles " << name2 << endl;
    Warrior& fighter1 = nametowarrior(name1,allwarriors);
    Warrior& fighter2 = nametowarrior(name2,allwarriors);
    if (fighter1.strength == 0){
        if (fighter2.strength == 0){
            cout << "Oh, NO! They're both dead! Yuck!" << endl;
        }else{
            cout << "He is dead, " << fighter2.name << endl;
        }
    }else{
        if (fighter2.strength == 0){
            cout << "He is dead, " << fighter1.name << endl;
        }else if (fighter1.strength > fighter2.strength){
            cout << fighter1.name << " defeats " << fighter2.name << endl;
            fighter1.strength -= fighter2.strength;
            fighter2.strength = 0;
        }else if (fighter1.strength < fighter2.strength){
            cout << fighter2.name << " defeats " << fighter1.name << endl;
            fighter1.strength = 0;
            fighter2.strength -= fighter1.strength;
        }else{
            cout << "Mutual Annihilation: " << fighter1.name << " and " << fighter2.name <<
            " die at each other's hands" << endl;
            fighter1.strength = fighter2.strength = 0;
        }
    }
}
