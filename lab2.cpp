#include <iostream>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
using namespace std;

struct compound{
    vector<string> name;
    int numofcarbon, numofhydrogen;
};

void getfile(ifstream& ifs){
    string name;
    cout << "What's the filename?" << endl;
    cin >> name;
    ifs.open(name);
    while (!ifs){
        ifs.clear();
        cout << "Add another name" << endl;
        cin >> name;
        ifs.open(name);
    }

}

void readfile(vector<compound>& allchem, ifstream& ifs){
    string name;
    char skip;
    int numC,numH;
    while (ifs >> name >> skip >> numC >> skip >> numH){
        compound mychem;
        bool add = true;
        mychem.numofcarbon = numC;
        mychem.numofhydrogen = numH;
        mychem.name.push_back(name);
        for (compound& elem: allchem){
            if (elem.numofcarbon == numC &&
                    elem.numofhydrogen == numH){
                elem.name.push_back(name);
                add = false;
            }
        }
        if(add)
        allchem.push_back(mychem);
    }
}

void sort(vector<compound> & allchem){
    compound temp;
    for (size_t i = 0; i < allchem.size(); ++i){
        for (size_t j = i; j < allchem.size(); ++j){
            if (allchem[j].numofcarbon < allchem[i].numofcarbon ||
                    (allchem[j].numofcarbon==allchem[i].numofcarbon &&
                    allchem[j].numofhydrogen < allchem[i].numofhydrogen)){
                temp = allchem[i];
                allchem[i] = allchem[j];
                allchem[j] = temp;
            }
        }
    }
}

void display(const vector<compound> & allchem){
    for (const compound& elem: allchem){
        cout << 'C' << elem.numofcarbon << 'H' << elem.numofhydrogen << " ";
        for (const string& name:elem.name){
            cout << name << " ";
        }
        cout << endl;
    }
}

int main() {
    vector<compound> allchem;
    ifstream ifs;
    getfile(ifs);
    readfile(allchem, ifs);
    sort(allchem);
    display(allchem);
    ifs.close();
    return 0;
}