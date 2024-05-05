#include "Student.h"
#include <iostream>

namespace PA3
{

	Student::Student() : name(""), ID(0), courses(nullptr), capacity(0), numCourses(0) {}

	Student::Student(const std::string &name, int ID) : name(name), ID(ID), courses(nullptr), capacity(0), numCourses(0) {}

	Student::~Student()
	{
		delete[] courses; // Delete dynamically allocated array
	}

	const std::string &Student::getName() const
	{
		return name;
	}

	void Student::setName(const std::string &name)
	{
		this->name = name;
	}

	int Student::getID() const
	{
		return ID;
	}

	void Student::setID(int ID)
	{
		this->ID = ID;
	}

	void Student::addCourse(Course *course)
	{
		if (numCourses == capacity)
		{
			// Resize the array if needed
			capacity = (capacity == 0) ? 1 : capacity * 2;
			Course **temp = new Course *[capacity];
			for (int i = 0; i < numCourses; ++i)
			{
				temp[i] = courses[i];
			}
			delete[] courses;
			courses = temp;
		}
		courses[numCourses++] = course;
	}

	void Student::removeCourse(Course *course)
	{
		int index = -1;
		for (int i = 0; i < numCourses; ++i)
		{
			if (courses[i] == course)
			{
				index = i;
				break;
			}
		}
		if (index != -1)
		{
			for (int i = index; i < numCourses - 1; ++i)
			{
				courses[i] = courses[i + 1];
			}
			numCourses--;
		}
	}

	void Student::displayCourses() const
	{
		// Print student's name and ID
		std::cout << "Courses enrolled by " << name << " (ID: " << ID << "):" << std::endl;

		// Check if the student is enrolled in any courses
		if (numCourses == 0)
		{
			// No courses enrolled, print message
			//std::cout << "No courses enrolled." << std::endl;
		}
		else
		{
			// Print the IDs of the courses the student is enrolled in
			for (int i = 0; i < numCourses; ++i)
			{
				std::cout << courses[i] << std::endl;
			}
		}
	}

	Course *Student::getCourse(int index) const
	{
		if (index >= 0 && index < numCourses)
		{
			return courses[index];
		}
		return nullptr;
	}

	int Student::getNumCourses() const
	{
		return numCourses;
	}

} // namespace PA3
