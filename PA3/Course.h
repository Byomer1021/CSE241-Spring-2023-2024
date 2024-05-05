#pragma once

#include <string>

namespace PA3
{

	class Course
	{

	public:
		Course();
		Course(const std::string &name, const std::string &code);
		~Course();

		const std::string &getName() const;
		void setName(const std::string &name);

		const std::string &getCode() const;
		void setCode(const std::string &code);

		void addStudent(int studentID);
		void removeStudent(int studentID);
		void displayStudents() const;

	private:
		std::string name;
		std::string code;
		int *students;
		int capacity;
		int numStudents;
	};

}
