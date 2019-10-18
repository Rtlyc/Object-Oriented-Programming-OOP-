//
// Created by 刘禹辰 on 2019-10-18.
//
#include <vector>
#include <iostream>
#include "Registrar.h"
#include "Course.h"
#include "Student.h"
using namespace std;

namespace lab7 {
// implement Registrar
    ostream &operator<<(ostream &os, const Registrar &rhs) {
        os << "Registrar's Report" << endl;
        os << "Courses: " << endl;
        for (Course *eachcourse: rhs.courses) {
            os << *eachcourse;
        }
        os << "Students:" << endl;
        for (Student *eachstudent: rhs.students) {
            os << *eachstudent;
        }
        return os;
    }

    Registrar::Registrar() {}

    bool Registrar::addCourse(const string &coursename) {
        if (findCourse(coursename) < courses.size()) {
            return false;
        } else {
            courses.push_back(new Course(coursename));
            return true;
        }
    }

    bool Registrar::addStudent(const string &studentname) {
        if (findStudent(studentname) < students.size()) {
            return false;
        } else {
            students.push_back(new Student(studentname));
            return true;
        }
    }

    bool Registrar::enrollStudentInCourse(const string &studentName,
                                          const string &courseName) {
        size_t studentind = findStudent(studentName);
        size_t courseind = findCourse(courseName);
        if (studentind == students.size()) {
            cerr << " Students Not Exist";
            return false;
        }
        if (courseind == courses.size()) {
            cerr << " Courses Not Exist";
            return false;
        }
        Student *student = students[studentind];
        Course *course = courses[courseind];
        course->addStudent(student);
        student->addCourse(course);
        return true;

    }

    bool Registrar::cancelCourse(const string &courseName) {
        size_t index = findCourse(courseName);
        if (index == courses.size()) return false;
        Course *acourse = courses[index];
        acourse->removeStudentsFromCourse();
        delete courses[index];
        courses[index] = courses.back();
        courses.pop_back();
        return true;
    }

    void Registrar::purge() {
        for (Course *acourse: courses) {
            delete acourse;
            acourse = nullptr;
        }
        courses.clear();
        for (Student *astudent: students) {
            delete astudent;
            astudent = nullptr;
        }
        students.clear();
    }

    size_t Registrar::findStudent(const string &studentname) const {
        for (size_t index = 0; index < students.size(); ++index) {
            if (students[index]->getName() == studentname) {
                return index;
            }
        }
        return students.size();
    }

    size_t Registrar::findCourse(const string &coursename) const {
        for (size_t index = 0; index < courses.size(); ++index) {
            if (courses[index]->getName() == coursename) {
                return index;
            }
        }
        return courses.size();
    }
}