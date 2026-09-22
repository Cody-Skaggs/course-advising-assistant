#pragma once

#include <string>
#include <vector>

struct Course {
	std::string courseNumber;
	std::string courseName;
	std::vector<std::string> prerequisites;
};