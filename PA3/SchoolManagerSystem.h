#ifndef SCHOOL_MANAGER_SYSTEM_H
#define SCHOOL_MANAGER_SYSTEM_H

#include "Student.h"
#include "Course.h"

namespace PA3
{

	class SchoolManagerSystem
	{

	public:
		// Constructor and destructor
		SchoolManagerSystem();
		~SchoolManagerSystem();

		// Display main menu
		void displayMenu() const;

		// Execute menu choice
		void executeMenuChoice(int choice);

		// Student menu functions
		void studentMenu();
		void addStudent();
		void selectStudent();

		// Course menu functions
		void courseMenu();
		void addCourse();
		void selectCourse();

		// Display all students and courses
		void displayAllStudents() const;
		void displayAllCourses() const;

		// Function to add selected student to a course
		void addSelectedStudentToCourse();
		// Function to drop selected student from a course
		void dropSelectedStudentFromCourse();

		void studentSubMenu();
		void deleteSelectedStudent();
		void courseSubMenu();
		void listStudentsRegisteredToSelectedCourse();
		void deleteCourse();

	private:
		// Data members for storing students and courses
		Student *students;
		int studentCapacity;
		int numStudents;
		Course *courses;
		int courseCapacity;
		int numCourses;
		// Pointer to selected student and course
		Student *selectedStudent;
		Course *selectedCourse;
	};

} // namespace PA3

#endif // SCHOOL_MANAGER_SYSTEM_H
