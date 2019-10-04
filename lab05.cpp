#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Section{
    friend ostream& operator<<(ostream& os, const Section& asection);
    class Timeslot{
        friend ostream& operator<<(ostream& os, const Timeslot& timeslot){
            string period = "am";
            int time = timeslot.timeoftheday;
            if (timeslot.timeoftheday > 12){
                time -= 12;
                period = "pm";
            }
            os << "[Day: " << timeslot.day << ", Start time: " << time << period << "]";
            return os;
        };
    public:
        Timeslot(const string& name, int time):day(name),timeoftheday(time){}
    private:
        string day;
        int timeoftheday;
    };

    class Student{
        friend ostream& operator<<(ostream& os, const Student& astudent){
            os << "Name: " << astudent.studentname << ", Grades: ";
            for (int k: astudent.allgrades){
                os << k << " ";
            }
            return os;
        };
    public:
        Student(const string& name):studentname(name), allgrades(14,-1){}
        void addmygrade(int grade, int week){
            allgrades[week-1] = grade;
        }
        const string& getName() const{
            return studentname;
        }

    private:
        string studentname;
        vector<int> allgrades;
    };
public:
    Section(const string& sectionname, const string& day, int time):sectionname(sectionname),time(day,time){};
    void addStudent(const string& name){
        allstudents.push_back(new Student(name));
    };
    Student* GetStudent(const string& name) const{
        for(size_t index = 0; index < allstudents.size(); ++index){
            if (allstudents[index] -> getName() == name){
                return allstudents[index];
            }
        }
    }
    Section(const Section& asection):sectionname(asection.sectionname),time(asection.time){
        for(Student* astudent: asection.allstudents){
            allstudents.push_back(new Student(*astudent));
        }
    }
    ~Section(){
        cout << "Section " << sectionname << " is being deleted" << endl;
        for(Student* astudent: allstudents){
            cout << "Deleting " << astudent->getName() << endl;
            delete astudent;
        }
    }
private:
    string sectionname;
    Timeslot time;
    vector<Student*> allstudents;
};


class LabWorker{
    friend ostream& operator<<(ostream& os, const LabWorker& labworker);
public:
    LabWorker(const string& name): labworkername(name){};
    void addSection(Section& asection){
        mysection = &asection;
    };
    void addGrade(const string& name,int grade, int week){
        mysection->GetStudent(name) ->addmygrade(grade,week);
    };
private:
    string labworkername;
    Section* mysection;
};

ostream& operator<<(ostream& os, const LabWorker& labworker);
ostream& operator<<(ostream& os, const Section& asection);
void doNothing(Section sec);

int main() {

    cout << "Test 1: Defining a section\n";
    Section secA2("A2", "Tuesday", 16);
    cout << secA2 << endl;

    cout << "\nTest 2: Adding students to a section\n";
    secA2.addStudent("John");
    secA2.addStudent("George");
    secA2.addStudent("Paul");
    secA2.addStudent("Ringo");
    cout << secA2 << endl;

    cout << "\nTest 3: Defining a lab worker.\n";
    LabWorker moe("Moe");
    cout << moe << endl;

    cout << "\nTest 4: Adding a section to a lab worker.\n";
    moe.addSection(secA2);
    cout << moe << endl;

    cout << "\nTest 5: Adding a second section and lab worker.\n";
    LabWorker jane( "Jane" );
    Section secB3( "B3", "Thursday", 11 );
    secB3.addStudent("Thorin");
    secB3.addStudent("Dwalin");
    secB3.addStudent("Balin");
    secB3.addStudent("Kili");
    secB3.addStudent("Fili");
    secB3.addStudent("Dori");
    secB3.addStudent("Nori");
    secB3.addStudent("Ori");
    secB3.addStudent("Oin");
    secB3.addStudent("Gloin");
    secB3.addStudent("Bifur");
    secB3.addStudent("Bofur");
    secB3.addStudent("Bombur");
    jane.addSection(secB3);
    cout << jane << endl;

    cout << "\nTest 6: Adding some grades for week one\n";
    moe.addGrade("John", 17, 1);
    moe.addGrade("Paul", 19, 1);
    moe.addGrade("George", 16, 1);
    moe.addGrade("Ringo", 7, 1);
    cout << moe << endl;

    cout << "\nTest 7: Adding some grades for week three (skipping week 2)\n";
    moe.addGrade("John", 15, 3);
    moe.addGrade("Paul", 20, 3);
    moe.addGrade("Ringo", 0, 3);
    moe.addGrade("George", 16, 3);
    cout << moe << endl;

    cout << "\nTest 8: We're done (almost)! \nWhat should happen to all "
         << "those students (or rather their records?)\n";

    cout << "\nTest 9: Oh, IF you have covered copy constructors in lecture, "
         << "then make sure the following call works properly, i.e. no memory leaks\n";
    doNothing(secA2);
    cout << "Back from doNothing\n\n";

}


ostream& operator<<(ostream& os, const Section& asection){
    os << "Section: " << asection.sectionname << ", " << asection.time << ", Students: ";
    if (asection.allstudents.size()) {
        os << endl;
        for (size_t index = 0; index < asection.allstudents.size(); ++index) {
            os << *asection.allstudents[index] << endl;
        }
    } else{
        os << "None";
    }
    return os;
}

ostream& operator<<(ostream& os, const LabWorker& labworker){
    if (labworker.mysection) {
        os << labworker.labworkername << " has " << *labworker.mysection;
    }else{
        os << labworker.labworkername << " does not have a section";
    }
    return os;
}

void doNothing(Section sec){
    cout << sec << endl;
}
