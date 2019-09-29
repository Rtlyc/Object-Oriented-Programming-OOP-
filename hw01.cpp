#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

//First, write a function that takes an encrypted character and returns the corresponding decrypted character.
//Note that only lowercase characters will result in a change. For all other characters,
//the function will return the input value.
//(Note that the function's return type will need to be char.)

char corresponding(char digit,int step){
    if (digit <= 'z' && digit >= 'a') {
        digit -= step;
        if (!(digit <= 'z' && digit >= 'a')) {
            digit += 26;
        }
    }
    return digit;
}

//modify an encrypted string changing it into it into it unencrypted form
void modify(string & line, int step){
    for (char& letter: line){
        letter = corresponding(letter,step);
    }
}

int main() {
    //read the file, and save as variable ifs
    ifstream encryptedfile("encrypted.txt");
    if (!encryptedfile){
        cerr << "Couldn't open the file.\n";
        exit(1);
    }
    //save the steps as int variable step
    int step;
    encryptedfile >> step;
    //use a vector to save each line of the file
    string line;
    vector<string> array;
    //iterate through each line and decrypt
    while (getline(encryptedfile,line)){
        modify(line,step);
        array.push_back(line);
    }
    //use a while loop to output the last line and pop it every time
    while (array.size()>1){
        cout << array.back() << endl;
        array.pop_back();
    }
    encryptedfile.close();
    return 0;
}
