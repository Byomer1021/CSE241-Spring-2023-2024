#pragma once
#include "Course.h"
#include <string>

namespace PA3
{

	class Student
	{

	public:
		Student();
		Student(const std::string &name, int ID);
		~Student();

		const std::string &getName() const;
		void setName(const std::string &name);

		int getID() const;
		void setID(int ID);

		void addCourse(Course *course);
		void removeCourse(Course *course);
		Course *getCourse(int index) const;
		int getNumCourses() const;
		void displayCourses() const;

	private:
		std::string name;
		int ID;
		Course **courses;
		int capacity;
		int numCourses;
	};

}
