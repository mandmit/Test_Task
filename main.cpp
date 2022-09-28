#include <fstream>
#include <array>
#include <chrono>
#include "Date.h"
#include "Month_Year.h"

#define time_point std::chrono::steady_clock::now()

int main() {
	try {
		std::string out_file_name, in_file_name;
		std::map<std::pair<std::string, Month_Year>, int> records;
		std::cout << "Enter name of file with data. //Example: Data_file.csv//: ";
		std::cin >> in_file_name;
		std::cout << "\nEnter new name of report. //Example: Report_file.csv//: ";
		std::cin >> out_file_name;
		std::ifstream in;
		std::ofstream out;
		char separator = '0';
		in.open(in_file_name);
		out.open(out_file_name);
		std::array<int, 3> col{}; //col[0] - number of name column, col[1] - number of date column, col[2] - number of hours column
		int cnt = 0;
		auto start = time_point;
		std::string t_str;
		std::getline(in, t_str);
		std::stringstream sstream(t_str);
		t_str.clear();
		while (sstream) {
			if (separator == '0') {
				char temp_c;
				sstream >> temp_c;
				if (isalpha(temp_c) || isspace(temp_c) || isdigit(temp_c)) {
					t_str.push_back(temp_c);
				}
				else {
					separator = temp_c;
				}
			}
			else {
				std::getline(sstream, t_str, separator);
				cnt++;
			}
			if (t_str == "Name") {
				col[0] = cnt;
				t_str.clear();
			}
			else if (t_str == "date") {
				col[1] = cnt;
				t_str.clear();
			}
			else if (t_str.find("hours") != std::string::npos) {
				col[2] = cnt;
				t_str.clear();
			}
		}
		auto end = time_point;
		std::chrono::duration<double> elapsed_seconds = end - start;
		std::cout << '\n' << "Time to count all columns and find separator: " << elapsed_seconds.count() << " s\n";
		const int max_column = cnt;
		cnt = 0;
		start = time_point;
		out << "Name" << separator << "Month" << separator << "Total hours\n";
		std::pair<std::string, Month_Year> temp_p;
		while (in) {
			std::string temp;
			if (cnt + 1 != max_column) {
				std::getline(in, temp, separator);
			}
			else {
				std::getline(in, temp);
			}
			if (col[0] == cnt) {
				temp_p.first = temp;
			}
			else if (col[1] == cnt) {
				temp_p.second = convert(temp);
			}
			else if (col[2] == cnt) {
				records[temp_p] += std::stoi(temp);
			}
			cnt++;
			if (cnt == max_column) {
				cnt = 0;
			}
		}
		end = time_point;
		elapsed_seconds = end - start;
		std::cout << '\n' << "Time to parce all data from file: " << elapsed_seconds.count() << " s\n";
		start = time_point;
		for (const auto& el : records) {
			out << el.first.first << separator << el.first.second.month << ' ' << el.first.second.year << separator << el.second << '\n';
		}
		end = time_point;
		elapsed_seconds = end - start;
		std::cout << '\n' << "Time to write all data into file: " << elapsed_seconds.count() << " s\n";
		in.close();
		out.close();
	}
	catch (std::exception& ex) {
		std::cout << ex.what() << '\n';
	}
	return 0;
}