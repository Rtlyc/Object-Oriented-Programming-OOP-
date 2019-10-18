//
// Created by 刘禹辰 on 2019-10-18.
//

#include "Student.h"
#include "Course.h"
#include <vector>
#include <iostream>
using namespace std;

namespace lab7 {
// implement Student
    ostream &operator<<(ostream &os, const Student &rhs) {
        os << rhs.getName() << ": ";
        for (Course *acourse: rhs.courses) {
            os << acourse->getName() << " ";
        }
        if (rhs.courses.empty()) {
            os << " No Courses";
        }
        os << endl;
        return os;
    }

    Student::Student(const string &name) : name(name) {}

    const string &Student::getName() const { return name; }

    bool Student::addCourse(Course *acourse) {
        if (findCourse(acourse) == courses.size()) {
            courses.push_back(acourse);
            return true;
        }
        return false;
    }

    size_t Student::findCourse(Course *acourse) {
        for (size_t index = 0; index < courses.size(); ++index) {
            if (courses[index] == acourse) {
                return index;
            }
        }
        return courses.size();
    }

    void Student::removedFromCourse(Course *acourse) {
        size_t index = findCourse(acourse);
        courses[index] = courses.back();
        courses.pop_back();
    }
}