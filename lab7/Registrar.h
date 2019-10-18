//
// Created by 刘禹辰 on 2019-10-18.
//

#ifndef LAB07_REGISTRAR_H
#define LAB07_REGISTRAR_H

#include <string>
#include <vector>
#include <iostream>


namespace lab7 {
    class Course;
    class Student;

    class Registrar {
        friend std::ostream &operator<<(std::ostream &os, const Registrar &rhs);

    public:
        Registrar();

        bool addCourse(const std::string &coursename);

        bool addStudent(const std::string &studentname);

        bool enrollStudentInCourse(const std::string &studentName,
                                   const std::string &courseName);

        bool cancelCourse(const std::string &courseName);

        void purge();

    private:
        size_t findStudent(const std::string &studentname) const;

        size_t findCourse(const std::string &coursename) const;


        std::vector<Course *> courses;
        std::vector<Student *> students;
    };
}

#endif //LAB07_REGISTRAR_H
