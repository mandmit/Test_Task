#pragma once
#include <iostream>

class Date {
public:
	Date();
	Date(int y, int m, int d);
	int getYear() const;
	void setYear(int y);
	int getMonth() const;
	void setMonth(int m);
	int getDay() const;
	void setDay(int d);
	void updDate(int y, int m, int d);
private:
	int year;
	int month;
	int day;
};

std::istream& operator >> (std::istream& stream, Date& date);