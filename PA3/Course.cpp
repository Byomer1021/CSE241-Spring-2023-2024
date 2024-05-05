#include "Course.h"
#include <iostream>

namespace PA3 {

    Course::Course() : name(""), code(""), students(nullptr), capacity(0), numStudents(0) {}

    Course::Course(const std::string& name, const std::string& code) : name(name), code(code), students(nullptr), capacity(0), numStudents(0) {}

    Course::~Course() {
        delete[] students; // Delete dynamically allocated array
    }

    const std::string& Course::getName() const {
        return name;
    }

    void Course::setName(const std::string& name) {
        this->name = name;
    }

    const std::string& Course::getCode() const {
        return code;
    }

    void Course::setCode(const std::string& code) {
        this->code = code;
    }

    void Course::addStudent(int studentID) {
        // Check if the studentID already exists
        for (int i = 0; i < numStudents; ++i) {
            if (students[i] == studentID) {
                // Student is already enrolled in this course, print error message
               // std::cout << "Student is already enrolled in this course." << std::endl;
                return;
            }
        }

        // Increase capacity if necessary
        if (numStudents >= capacity) {
            int newCapacity = (capacity == 0) ? 1 : capacity * 2;
            int* temp = new int[newCapacity];
            for (int i = 0; i < numStudents; ++i) {
                temp[i] = students[i];
            }
            delete[] students; // Delete old array
            students = temp;
            capacity = newCapacity;
        }

        // Add studentID
        students[numStudents++] = studentID;
        //std::cout << "Student added successfully." << std::endl;
    }

    void Course::removeStudent(int studentID) {
        // Find the index of the studentID
        int index = -1;
        for (int i = 0; i < numStudents; ++i) {
            if (students[i] == studentID) {
                index = i;
                break;
            }
        }

        // If found, remove studentID
        if (index != -1) {
            for (int i = index; i < numStudents - 1; ++i) {
                students[i] = students[i + 1];
            }
            numStudents--;
            //std::cout << "Student removed successfully." << std::endl;
        } else {
            // Student not found, print error message
           // std::cout << "Student not found." << std::endl;
        }
    }

    void Course::displayStudents() const {
        // Print course name and code
        std::cout << "Students enrolled in course " << name << " (" << code << "):" << std::endl;
        
        // Check if any students are enrolled in the course
        if (numStudents == 0) {
            // No students enrolled, print message
            //std::cout << "No students enrolled." << std::endl;
        } else {
            // Print the IDs of the students enrolled in the course
            for (int i = 0; i < numStudents; ++i) {
                std::cout << students[i] << std::endl;
            }
        }
    }

} // namespace PA3
