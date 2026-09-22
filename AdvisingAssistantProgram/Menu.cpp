#include "Menu.h"
#include "BinarySearchTree.h"
#include "CourseLoader.h"

#include <iostream>
#include <limits>
#include <string>


void displayMenu();
int getMenuChoice();
void handleLoadCourses(BinarySearchTree& courseTree);
void handlePrintCourses(BinarySearchTree& courseTree);
void handleCourseSearch(BinarySearchTree& courseTree);


void runMenu(BinarySearchTree& courseTree) {
	int choice = 0;

	while (choice != 4) {
		displayMenu();
		choice = getMenuChoice();

		switch (choice) {
		case 1:
			handleLoadCourses(courseTree);
			break;
		case 2:
			handlePrintCourses(courseTree);
			break;
		case 3:
			handleCourseSearch(courseTree);
			break;
		case 4:
			std::cout << "Thank you for using the course planner!" << std::endl;
			break;
		}
	}
}

int getMenuChoice() {
	int choice;

	std::cout << "Enter your choice: ";
	std::cin >> choice;

	while (std::cin.fail() || choice < 1 || choice > 4) {
		std::cin.clear(); // clear the error flag
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // discard invalid input
		std::cout << "Invalid choice. Please enter a number between 1 and 4: ";
		std::cin >> choice;
	}
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // discard any remaining input

	return choice;
}

void handleLoadCourses(BinarySearchTree& courseTree) {
	std::string fileName;
	std::cout << "Please enter the name of your file with the extension: ";
	std::getline(std::cin, fileName);
	if (loadCourses(fileName, courseTree)) {
		std::cout << "Courses loaded successfully!" << std::endl;
	} else {
		std::cout << "Failed to load courses." << std::endl;
	}
}

void handlePrintCourses(BinarySearchTree& courseTree) {
	std::cout << "Courses in the system:" << std::endl;
	courseTree.printInOrder();
}

void handleCourseSearch(BinarySearchTree& courseTree) {
	std::string courseNumber;
	std::cout << "Enter the course number to search for: ";
	std::getline(std::cin, courseNumber);
	Course foundCourse = courseTree.search(courseNumber);
	if (!foundCourse.courseNumber.empty()) {
		std::cout << "Course found: " << foundCourse.courseNumber << " - " << foundCourse.courseName << std::endl;
		if (!foundCourse.prerequisites.empty()) {
			std::cout << "Prerequisites: ";
			for (const auto& prereq : foundCourse.prerequisites) {
				std::cout << prereq << " ";
			}
			std::cout << std::endl;
		} else {
			std::cout << "No prerequisites." << std::endl;
		}
	} else {
		std::cout << "Course not found." << std::endl;
	}
}

void displayMenu() {
	std::cout << "1: Load Data Structure" << std::endl;
	std::cout << "2: Print Course List" << std::endl;
	std::cout << "3: Print Course" << std::endl;
	std::cout << "4: Exit Program" << std::endl;
}