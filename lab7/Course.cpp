//
// Created by 刘禹辰 on 2019-10-18.
//

#include "Course.h"
#include <vector>
#include <iostream>
#include "Student.h"

using namespace std;

namespace lab7 {
// implement courses
    ostream &operator<<(ostream &os, const Course &rhs) {
        os << rhs.getName() << ": ";
        for (Student *astudent: rhs.students) {
            os << astudent->getName() << " ";
        }
        if (rhs.students.empty()) {
            os << " No Students";
        }
        os << endl;
        return os;
    }

    Course::Course(const string &courseName) : name(courseName) {}

    const string &Course::getName() const { return name; }

    bool Course::addStudent(Student *astudent) {
        if (findStudent(astudent) == students.size()) {
            students.push_back(astudent);
            return true;
        }
        return false;
    }

    size_t Course::findStudent(Student *astudent) {
        for (size_t index = 0; index < students.size(); ++index) {
            if (students[index] == astudent) {
                return index;
            }
        }
        return students.size();
    }

    void Course::removeStudentsFromCourse() {
        for (Student *astudent:students) {
            astudent->removedFromCourse(this);
        }
    }
}