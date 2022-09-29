#include <array>
#include "Date.h"
#include "Month_Year.h"
#include "Logger.h"

int main() {
	try {
		std::string out_file_name, in_file_name;
		std::map<std::pair<std::string, Month_Year>, int> parsing_records;
		std::cout << "Enter name of file with data. //Example: Data_file.csv//: ";
		std::cin >> in_file_name;
		std::cout << "\nEnter new name of report. //Example: Report_file.csv//: ";
		std::cin >> out_file_name;
		std::ifstream in;
		std::ofstream out;
		char separator = '0';
		in.open(in_file_name);
		if (!in.is_open()) {
			std::cout << "Error. There is no file with such name: " << in_file_name << '\n';
			return 0;
		}
		out.open(out_file_name);
		std::array<int, 3> col{-1,-1,-1}; //col[0] - number of name column, col[1] - number of date column, col[2] - number of hours column
		int cnt = 0;
		Logger log(in_file_name, out_file_name, "Finding separator and count columns.");
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
		log.EndPoint();
		for (auto el : col) {
			if (el == -1) {
				std::cout << "Failed! See Logs.txt last line about problem.";
				log.UpdStartPointAndMessage("Error! The needed column can't be found!");
				log.EndPoint();
				in.close();
				out.close();
				return 0;
			}
		}
		const int max_column = cnt;
		cnt = 0;
		out << "Name" << separator << "Month" << separator << "Total hours\n";
		log.UpdStartPointAndMessage("Reading and parsing data from input_file.");
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
				parsing_records[temp_p] += std::stoi(temp);
			}
			cnt++;
			if (cnt == max_column) {
				cnt = 0;
			}
		}
		log.EndPoint();
		log.UpdStartPointAndMessage("Writing data into output_file.");
		for (const auto& el : parsing_records) {
			out << el.first.first << separator << el.first.second.month << ' ' << el.first.second.year << separator << el.second << '\n';
		}
		log.EndPoint();
		in.close();
		out.close();
		std::cout << "\nCompleted";
	}
	catch (std::exception& ex) {
		std::cout << ex.what() << '\n';
	}
	return 0;
}