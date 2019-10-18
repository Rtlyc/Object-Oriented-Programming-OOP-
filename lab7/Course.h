//
// Created by 刘禹辰 on 2019-10-18.
//

#ifndef LAB07_COURSE_H
#define LAB07_COURSE_H

#include <string>
#include <vector>
#include <iostream>

namespace lab7 {
    class Student;

    class Course {
        friend std::ostream &operator<<(std::ostream &os, const Course &rhs);

    public:
        // Course methods needed by Registrar
        Course(const std::string &courseName);

        const std::string &getName() const;

        bool addStudent(Student *astudent);

        void removeStudentsFromCourse();

    private:
        size_t findStudent(Student *astudent);

        std::string name;
        std::vector<Student *> students;
    };
}

#endif //LAB07_COURSE_H
