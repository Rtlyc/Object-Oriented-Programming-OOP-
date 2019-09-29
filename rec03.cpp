#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

struct BankAccount{
    string name;
    int number;

};

class Account{
    friend ostream& operator<<(ostream& os, const Account& aPerson);
    class Transaction;
    string name;
    int number;
    int balance;
    vector<Transaction> history;
    class Transaction{
        friend ostream &operator<<(ostream &os, const Transaction &mytran) {
            string status;
            if (mytran.deposit){
                status = "Deposit ";
            }else{
                status = "Withdraw ";
            }
            os << status << mytran.moneyflow << endl;
            return os;
        };
        bool deposit;
        int moneyflow;
    public:
        Transaction(bool sta, int money):deposit(sta),moneyflow(money){}
    };
public:
    Account(const string& Aname, int Anumber, int Abalance = 0): name(Aname),number(Anumber),balance(Abalance){}
    const string& getName() const;
    int getNumber() const;
    ostream& operator<<(ostream& os);
    void deposit(int money);
    void withdraw(int money);
    void printhistory() const;
};

void openfile(const string& filename, ifstream& file);
void savedata(ifstream& file,vector<BankAccount>& accounts);
void savedata2(ifstream& file, vector<BankAccount>& accounts);
void display(vector<BankAccount>& accounts);
void savedata(ifstream& file, vector<Account>& allaccounts);
void savedata2(ifstream& file, vector<Account>& allaccounts);
ostream& operator<<(ostream& os,const Account& aPerson);
void display(const vector<Account>& allaccounts);
void readfile(const string& filename, ifstream& file);
Account& numbertoaccount(int num, vector<Account>& allaccounts);

int main() {
    vector<BankAccount> accounts;
    vector<Account> allaccounts;
    ifstream file;
    string status;
    openfile("accounts.txt",file);
    savedata(file,accounts);
    file.close();
//    display(accounts);
    accounts.clear();
    openfile("accounts.txt",file);
    savedata2(file,accounts);
    file.close();
//    display(accounts);
    accounts.clear();
    openfile("accounts.txt",file);
    savedata2(file,allaccounts);
//    display(allaccounts);
    file.close();
    allaccounts.clear();
    file.open("transactions.txt");
    while(file >> status){
        if(status == "Account"){
            string name;
            int number;
            file >> name >> number;
            allaccounts.emplace_back(name,number);
        }
        else if(status == "Deposit"){
            int accountnumber,moneyflow;
            file >> accountnumber >> moneyflow;
            Account& aperson = numbertoaccount(accountnumber,allaccounts);
            aperson.deposit(moneyflow);
        }
        else if(status == "Withdraw"){
            int accountnumber,moneyflow;
            file >> accountnumber >> moneyflow;
            Account& aperson = numbertoaccount(accountnumber,allaccounts);
            aperson.withdraw(moneyflow);
        }
    }
    file.close();
    for(const Account& person: allaccounts){
        cout << person;
        person.printhistory();
    }
    return 0;
}

void openfile(const string& filename, ifstream& file){
    file.open(filename);
}

void savedata(ifstream& file,vector<BankAccount>& accounts){
    string name;
    int number;
    BankAccount aperson;
    while (file >> name >> number){
        aperson.name = name;
        aperson.number = number;
        accounts.push_back(aperson);
    }
}

void display(vector<BankAccount>& accounts){
    for (BankAccount& aperson: accounts){
        cout << aperson.name << " " << aperson.number << endl;
    }
}

void savedata2(ifstream& file, vector<BankAccount>& accounts){
    string name;
    int number;
    while(file >> name >> number){
        accounts.push_back(BankAccount{name,number});
    }
}

const string& Account:: getName() const{
    return name;
}

int Account::getNumber() const{
    return number;
}

ostream& Account::operator<<(ostream& os){
    os << name << " " << number << endl;
    return os;
}

/*
ostream& operator<<(ostream& os,const Account& aPerson){
    os << aPerson.getName() << " " << aPerson.getNumber() << endl;
    return os;
}
*/

ostream& operator<<(ostream& os, const Account& aPerson){
    os << aPerson.name << " " << aPerson.number << endl;
    return os;
}


void savedata(ifstream& file, vector<Account>& allaccounts){
    string name;
    int number;
    while(file >> name >> number){
        allaccounts.push_back(Account(name,number));
    }
}


void savedata2(ifstream& file, vector<Account>& allaccounts){
    string name;
    int number;
    while(file >> name >> number){
        allaccounts.emplace_back(name,number);
    }
}

void display(const vector<Account>& allaccounts){
    for(const Account& aPerson: allaccounts){
        cout << aPerson;
    }
}

void Account::deposit(int money){
    history.emplace_back(true,money);
    balance += money;
}

void Account::withdraw(int money) {
    if(money > balance){
        cout << "Not enough money" << endl;
    }else{
        history.emplace_back(false,money);
        balance -= money;
    }
}

void Account::printhistory() const{
    for(const Transaction& mytran:history){
        cout << mytran;
    }
}

void readfile(const string& filename, ifstream& file){

}

Account& numbertoaccount(int num, vector<Account>& allaccounts){
    for(Account& aperson: allaccounts){
        if (aperson.getNumber() == num){
            return aperson;
        }
    }
}
