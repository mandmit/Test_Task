#include "Date.h"

Date::Date() : year(2020), month(1), day(1) {}
Date::Date(int y, int m, int d) {
	if (year < 0) {
		year = 2020;
	}
	else {
		year = y;
	}
	if (m < 1 || m > 12) {
		month = 1;
	}
	else {
		month = m;
	}
	if (d > 31 || d < 1) {
		day = 1;
	}
	else {
		day = d;
	}
}
int Date::getYear() const {
	return year;
}
void Date::setYear(int y) {
	year = y;
}
int Date::getMonth() const {
	return month;
}
void Date::setMonth(int m) {
	month = m;
}
int Date::getDay() const {
	return day;
}
void Date::setDay(int d) {
	day = d;
}
void Date::updDate(int y, int m, int d) {
	setYear(y);
	setMonth(m);
	setDay(d);
}

std::istream& operator >> (std::istream& stream, Date& date) {
	int y = 1, m = 1, d = 1;
	stream >> y; stream.ignore(1);
	stream >> m; stream.ignore(1);
	stream >> d; stream.ignore(1);
	date.updDate(y, m, d);
	return stream;
}