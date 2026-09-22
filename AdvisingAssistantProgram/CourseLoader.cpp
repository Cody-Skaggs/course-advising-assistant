#include "CourseLoader.h"

#include <fstream>
#include <iostream>
#include <sstream>

#include "BinarySearchTree.h"

bool loadCourses(const std::string& fileName, BinarySearchTree& courseTree) {
	std::fstream inFile;
	std::string line;

	inFile.open(fileName);

	if (!inFile) {
		return false;
	}

	std::cout << "File opened successfully" << std::endl;

	while (getline(inFile, line)) {
		if (line.empty()) {
			continue;
		}

		Course course;
		std::string prerequisite;
		std::stringstream ss(line);

		getline(ss, course.courseNumber, ',');
		getline(ss, course.courseName, ',');

		while (getline(ss, prerequisite, ',')) {
			if (!prerequisite.empty()) {
				course.prerequisites.push_back(prerequisite);
			}
		}

		courseTree.insert(course);
	}

	return true;
}