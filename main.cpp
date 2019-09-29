#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

void print(const string & line){
    cout << line << endl;
}


int main() {
    ifstream ifs("jabberwocky");
    if (!ifs){
        cerr << "Couldn't read the file"<< endl;
        exit(1);
    }
    int count = 0;
    string line;
    while (getline(ifs,line)){
        if (!line.empty()) {
            print(line);
        }
    }
    ifs.clear();
    ifs.seekg(0);
    string word;
    while (ifs >> word){
        print(word);
        count ++;
    }
    ifs.close();
    cout << "total words count: " << count << endl;
    return 0;
}