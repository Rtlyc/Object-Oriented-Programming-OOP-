/*
  Recitation 06
  CS2124
 
  Focus: Dynamic arrays and copy control
 */

#include <string>
#include <iostream>
using namespace std;

class Position {
    friend ostream& operator<<(ostream& os, const Position& rhs) {
        os << '[' << rhs.title << ',' << rhs.salary << ']';
        return os;
    }
public:
    Position(const string& aTitle, double aSalary)
            : title(aTitle), salary(aSalary) {}
    const string& getTitle() const { return title; }
    double getSalary() const { return salary; }
    void changeSalaryTo(double d) { salary = d; }
private:
    string title;
    double salary;
}; // class Position

class Entry {
    friend ostream& operator<<(ostream& os, const Entry& rhs) {
        os << rhs.name << ' ' << rhs.room
           << ' ' << rhs.phone << ", " << *rhs.pos;
        return os;
    }
public:
    Entry(const string& name, unsigned room, unsigned phone, Position& position)
            : name(name), room(room), phone(phone), pos(&position) {
    }
    const string& getName() const { return name; }
    unsigned getPhone() const { return phone; }
private:
    string name;
    unsigned room;
    unsigned phone;
    Position* pos;
}; // class Entry

class Directory {
    // Overload output operator
    friend ostream& operator<<(ostream& os, const Directory& adirectory){
        for(size_t index = 0; index < adirectory.size; ++ index){
            os << *(adirectory.entries[index]) << endl;
        }
        // need to implement
        return os;
    }
public:
    // Of course the first function you need to write for this (or
    // any) class is...
    // ???
    // ...
    Directory():size(0),capacity(1),entries(new Entry*[1]){}

    Directory(const Directory& other): size(other.size), capacity(other.capacity){
        entries = new Entry*[capacity];
        for (size_t index = 0; index < size; ++index){
            entries[index] = new Entry(*other.entries[index]);
        }

    }

    ~Directory(){
        for (size_t index = 0; index < size; ++index){
            delete entries[index];
        }
        delete[] entries;
    }

    Directory& operator=(const Directory& other){
        if(&other != this){
            for (size_t index = 0; index < size; ++index){
                delete entries[index];
            }
            delete[] entries;
            entries = new Entry*[other.capacity];
            for (size_t index = 0; index < other.size; ++index){
                entries[index] = new Entry(*other.entries[index]);
            }
            size = other.size;
            capacity = other.capacity;
        }

        return *this;
    }

    // We'll get you started with the add method, but obviously you
    // have a lot of work to do here.
    void add(const string& name, unsigned room, unsigned ph, Position& pos) {
        if (size == capacity)	{
            // something is missing!!!  Add it!
            capacity *= 2;
            Entry** old = entries;
            entries = new Entry*[capacity];
            for(size_t index = 0; index < size; ++index){
                entries[index] = old[index];
            }
            delete [] old;


        } // if
        entries[size] = new Entry(name, room, ph, pos);
        ++size;
    } // add

    unsigned operator[](const string& name) const{
        for(size_t index = 0; index < size; ++index){
            if(entries[index]->getName() == name){
                return entries[index]->getPhone();
            }
        }
        return 0;
    }

private:
    Entry** entries;
    size_t size;
    size_t capacity;
}; // class Directory

void doNothing(Directory dir) { cout << dir << endl; }

int main() {

    // Note that the Postion objects are NOT on the heap.
    Position boss("Boss", 3141.59);
    Position pointyHair("Pointy Hair", 271.83);
    Position techie("Techie", 14142.13);
    Position peon("Peonissimo", 34.79);

    // Create a Directory
    Directory d;
    d.add("Marilyn", 123, 4567, boss);
    cout << d << endl;

    Directory d2 = d;	// What function is being used??
    d2.add("Gallagher", 111, 2222, techie);
    d2.add("Carmack", 314, 1592, techie);
    cout << d << endl;

    cout << "Calling doNothing\n";
    doNothing(d2);
    cout << "Back from doNothing\n";

    Directory d3;
    d3 = d2;

    // Should display 1592
    cout << d2["Carmack"] << endl;

} // main
