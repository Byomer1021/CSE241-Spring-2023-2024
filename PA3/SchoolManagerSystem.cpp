#include "SchoolManagerSystem.h"
#include <iostream>
using namespace std;

namespace PA3
{

	SchoolManagerSystem::SchoolManagerSystem() : courses(nullptr), courseCapacity(0), numCourses(0), students(nullptr), studentCapacity(0), numStudents(0), selectedStudent(nullptr), selectedCourse(nullptr) {}

	SchoolManagerSystem::~SchoolManagerSystem()
	{
		delete[] courses;
		delete[] students;
		delete selectedStudent;
		delete selectedCourse;
	}

	// Displays the main menu options
	void SchoolManagerSystem::displayMenu() const
	{
		cout << "Main_Menu:" << endl;
		cout << "0. Exit" << endl;
		cout << "1. Student" << endl;
		cout << "2. Course" << endl;
		cout << "3. List all students" << endl;
		cout << "4. List all courses" << endl;
	}

	// Executes the choice made by the user in the main menu
	void SchoolManagerSystem::executeMenuChoice(int choice)
	{
		switch (choice)
		{
		case 0:
			cout << "Exiting..." << endl;
			break;
		case 1:
			studentMenu();
			break;
		case 2:
			courseMenu();
			break;
		case 3:
			displayAllStudents();
			break;
		case 4:
			displayAllCourses();
			break;
		default:

			break;
		}
	}

	// Displays the student menu options
	void SchoolManagerSystem::studentMenu()
	{
		int choice;
		do
		{
			std::cout << "Student Menu:" << std::endl;
			std::cout << "0. Up" << std::endl;
			std::cout << "1. Add Student" << std::endl;
			std::cout << "2. Select Student" << std::endl;
			std::cin >> choice;
			switch (choice)
			{
			case 0:
				return;
			case 1:
				addStudent();
				break;
			case 2:
				selectStudent();
				if (selectedStudent != nullptr)
				{
					studentSubMenu(); // Call submenu for new student
				}
				break;
			default:

				break;
			}
		} while (choice != 0);
	}

	// Displays the submenu options for a selected student
	void SchoolManagerSystem::studentSubMenu()
	{
		int choice;
		do
		{
			std::cout << "Selected Student Menu:" << std::endl;
			std::cout << "0. Up" << std::endl;
			std::cout << "1. Delete Student" << std::endl;
			std::cout << "2. Add Selected Student to a Course" << std::endl;
			std::cout << "3. Drop Selected Student from a Course" << std::endl;
			std::cin >> choice;
			switch (choice)
			{
			case 0:
				return;
			case 1:
				deleteSelectedStudent();
				return; // When the student is deleted, return to the previous menu
			case 2:
				addSelectedStudentToCourse();
				break;
			case 3:
				dropSelectedStudentFromCourse();
				break;
			default:

				break;
			}
		} while (choice != 0);
	}

	// Adds a new student to the system
	void SchoolManagerSystem::addStudent()
	{
		string name;
		int ID;
		cin >> name >> ID;
		Student newStudent(name, ID); // Create a new student object

		// Resize the array if needed
		if (numStudents == studentCapacity)
		{
			// Double the capacity to allow for more students
			studentCapacity = (studentCapacity == 0) ? 1 : studentCapacity * 2;
			Student *temp = new Student[studentCapacity];
			// Copy existing students to the new array
			for (int i = 0; i < numStudents; ++i)
			{
				temp[i] = students[i];
			}
			delete[] students; // Deallocate old array
			students = temp;   // Update pointer to new array
		}

		// Add the new student to the array
		students[numStudents++] = newStudent;
	}

	// Selects a student based on the provided name and ID
	void SchoolManagerSystem::selectStudent()
	{
		string name;
		int ID;
		cin >> name >> ID;

		// Search for the student by name and ID
		bool found = false;
		for (int i = 0; i < numStudents; ++i)
		{
			if (students[i].getName() == name && students[i].getID() == ID)
			{
				selectedStudent = &students[i];
				found = true;
				break;
			}
		}

		if (!found)
		{
			return;
		}
	}

	// Displays the course menu options
	void SchoolManagerSystem::courseMenu()
	{
		int choice;
		do
		{
			cout << "0. Up" << endl;
			cout << "1. Add Course" << endl;
			cout << "2. Select Course" << endl;
			cin >> choice;
			switch (choice)
			{
			case 0:
				return;
			case 1:
				addCourse();
				break;
			case 2:
				selectCourse();
				break;
			default:

				break;
			}
		} while (choice != 0);
	}

	// Displays the submenu options for a selected course
	void SchoolManagerSystem::courseSubMenu()
	{
		int choice;
		do
		{
			std::cout << "Selected Course Menu:" << std::endl;
			std::cout << "0. Up" << std::endl;
			std::cout << "1. Delete Course" << std::endl;
			std::cout << "2. List_Students_Registered_to_the_Selected_Course" << std::endl;
			std::cin >> choice;
			switch (choice)
			{
			case 0:
				selectedCourse = nullptr; // Remove course choice
				return;
			case 1:
				deleteCourse();
				return;
			case 2:
				listStudentsRegisteredToSelectedCourse();
				break;
			default:
				break;
			}
		} while (choice != 0);
	}

	// Adds a new course to the system
	void SchoolManagerSystem::addCourse()
	{
		string code, name;

		// Clear the input buffer
		cin.ignore(1000, '\n');

		// Read the entire line for course name
		getline(cin, name);

		// Read the course code
		cin >> code;

		Course newCourse(code, name); // Create a new course object

		// Resize the array if needed
		if (numCourses == courseCapacity)
		{
			// Double the capacity to allow for more courses
			courseCapacity = (courseCapacity == 0) ? 1 : courseCapacity * 2;
			Course *temp = new Course[courseCapacity];
			// Copy existing courses to the new array
			for (int i = 0; i < numCourses; ++i)
			{
				temp[i] = courses[i];
			}
			delete[] courses; // Deallocate old array
			courses = temp;	  // Update pointer to new array
		}

		// Add the new course to the array
		courses[numCourses++] = newCourse;
	}

	// Selects a course based on the provided code and name
	void SchoolManagerSystem::selectCourse()
	{
		std::string courseCode, courseName;
		//std::cout << "Enter course code: ";
		std::cin >> courseCode;
		//std::cout << "Enter course name: ";
		cin.ignore(1000, '\n'); // Ignore newline character left in the buffer
		std::getline(std::cin, courseName);

		// Find and select the course
		selectedCourse = nullptr;
		for (int i = 0; i < numCourses; ++i)
		{
			if (courses[i].getCode() == courseCode && courses[i].getName() == courseName)
			{
				selectedCourse = &courses[i];
				break;
			}
		}

		if (selectedCourse != nullptr)
		{
			courseSubMenu(); // Call submenu for selectred course
		}
		else
		{
			return;
		}
	}

	// Displays information of all registered students
	void SchoolManagerSystem::displayAllStudents() const
	{
		if (numStudents == 0)
		{
			return;
		}
		else
		{
			for (int i = 0; i < numStudents; ++i)
			{
				cout << "Name: " << students[i].getName() << endl;
				cout << "ID: " << students[i].getID() << endl;
				cout << endl;
			}
		}
	}

	// Displays information of all registered courses
	void SchoolManagerSystem::displayAllCourses() const
	{
		if (numCourses == 0)
		{
			return;
		}
		else
		{
			for (int i = 0; i < numCourses; ++i)
			{
				cout << "Name: " << courses[i].getName() << endl;
				cout << "Code: " << courses[i].getCode() << endl;
				cout << endl;
			}
		}
	}

	// Adds the selected student to a course
	void SchoolManagerSystem::addSelectedStudentToCourse()
	{
		if (selectedStudent == nullptr)
		{
			return;
		}

		while (true)
		{
			std::cout << "0. Up" << std::endl;

			// List courses that are not added to the selected student
			int index = 1;
			for (int i = 0; i < numCourses; ++i)
			{
				bool enrolled = false;
				for (int j = 0; j < selectedStudent->getNumCourses(); ++j)
				{
					if (selectedStudent->getCourse(j) == &courses[i])
					{
						enrolled = true;
						break;
					}
				}
				if (!enrolled)
				{
					std::cout << index++ << ". " << courses[i].getName() << std::endl;
				}
			}

			int choice;

			std::cin >> choice;
			if (choice == 0)
			{
				return; // End the loop if "0. Up" option is selected
			}
			else if (choice >= 1 && choice <= numCourses)
			{
				Course *selectedCourse = nullptr;
				index = 1;
				for (int i = 0; i < numCourses; ++i)
				{
					bool enrolled = false;
					for (int j = 0; j < selectedStudent->getNumCourses(); ++j)
					{
						if (selectedStudent->getCourse(j) == &courses[i])
						{
							enrolled = true;
							break;
						}
					}
					if (!enrolled)
					{
						if (index == choice)
						{
							selectedCourse = &courses[i];
							break;
						}
						index++;
					}
				}

				if (selectedCourse != nullptr)
				{
					selectedStudent->addCourse(selectedCourse);
					return;
				}
				else
				{
					return;
				}
			}
			else
			{
				return;
			}
		}
	}

	void SchoolManagerSystem::dropSelectedStudentFromCourse()
	{
		if (selectedStudent == nullptr)
		{
			return;
		}

		// List courses that the selected student is enrolled in
		for (int i = 0; i < selectedStudent->getNumCourses(); ++i)
		{
			std::cout << i + 1 << ". " << selectedStudent->getCourse(i)->getName() << std::endl;
		}

		int choice;
		std::cin >> choice;

		if (choice >= 1 && choice <= selectedStudent->getNumCourses())
		{
			Course *droppedCourse = selectedStudent->getCourse(choice - 1);
			selectedStudent->removeCourse(droppedCourse);
		}
		else
		{
			return;
		}
	}

	// Deletes the selected student from the system
	void SchoolManagerSystem::deleteSelectedStudent()
	{
		if (selectedStudent == nullptr)
		{
			return;
		}

		// Remove student from list
		for (int i = 0; i < numStudents; ++i)
		{
			if (&students[i] == selectedStudent)
			{
				// Remove student from list
				for (int j = i; j < numStudents - 1; ++j)
				{
					students[j] = students[j + 1];
				}
				numStudents--;
				selectedStudent = nullptr; // Reset the selected student
				return;
			}
		}

		return;
	}

	// Lists all students registered to the selected course
	void SchoolManagerSystem::listStudentsRegisteredToSelectedCourse()
	{

		for (int i = 0; i < numStudents; ++i)
		{
			for (int j = 0; j < students[i].getNumCourses(); ++j)
			{
				if (students[i].getCourse(j) == selectedCourse)
				{
					std::cout << students[i].getName() << "   " << students[i].getID()   << std::endl;
					break;
				}
			}
		}
	}

	// Deletes the selected course from the system
	void SchoolManagerSystem::deleteCourse()
	{
		std::string courseCode, courseName;
		//std::cout << "Enter course code: ";
		std::cin >> courseCode;
		//std::cout << "Enter course name: ";
		cin.ignore(1000, '\n');
		std::getline(std::cin, courseName);

		if (courseCode.empty() || courseName.empty())
		{
			//std::cout << "Error: Course code or name cannot be empty." << std::endl;
			return;
		}

		bool courseFound = false;
		for (int i = 0; i < numCourses; ++i)
		{
			if (courses[i].getCode() == courseCode && courses[i].getName() == courseName)
			{
				// Remove course from list
				for (int j = i; j < numCourses - 1; ++j)
				{
					courses[j] = courses[j + 1];
				}
				numCourses--;
				courseFound = true;
				//std::cout << "Course deleted successfully." << std::endl;
				break; // Course found, end loop
			}
		}

		if (!courseFound)
		{
			return;
		}
	}

} // namespace PA3
