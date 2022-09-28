#include "Month_Year.h"
#include "Date.h"

const std::map<int, std::string> Month{ {1,"January"},{2,"February"}, {3,"March"},
	{4,"April"},{5, "May"}, {6, "June"}, {7, "July"}, {8, "August"}, {9, "September"},
	{10, "October"}, {11, "November"}, {12, "December"} };

Month_Year convert(const std::string& str) {
	Month_Year m_y;
	std::stringstream stream(str);
	Date date;
	stream >> date;
	m_y.month = Month.at(date.getMonth());
	m_y.year = date.getYear();
	return m_y;
}

bool operator < (const Month_Year& left, const Month_Year& right) {
	if (left.year == right.year) {
		return left.month < right.month;
	}
	else {
		return left.year < right.year;
	}
}