//
// Created by 刘禹辰 on 2019-10-18.
//

#ifndef LAB07_STUDENT_H
#define LAB07_STUDENT_H

#include <string>
#include <vector>
#include <iostream>

namespace lab7 {
    class Course;

    class Student {
        friend std::ostream &operator<<(std::ostream &os, const Student &rhs);

    public:
        // Student methods needed by Registrar
        Student(const std::string &name);

        const std::string &getName() const;

        bool addCourse(Course *acourse);

        // Student method needed by Course
        void removedFromCourse(Course *acourse);

    private:
        size_t findCourse(Course *acourse);

        std::string name;
        std::vector<Course *> courses;
    };
}
#endif //LAB07_STUDENT_H
