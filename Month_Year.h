#pragma once
#include <string>
#include <sstream>
#include <map>

struct Month_Year {
	std::string month = "";
	int year = 2020;
};

Month_Year convert(const std::string& str);

bool operator < (const Month_Year& left, const Month_Year& right);