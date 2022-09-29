#pragma once
#include <string>
#include <iostream>
#include <chrono>
#include <fstream>

using std::cout;
using std::chrono::duration_cast;
using std::chrono::system_clock;
using std::chrono::milliseconds;

class Logger {
public:
	Logger(const std::string& input_file_name, const std::string& output_file_name,
		const std::string& log_msg = "") : start(system_clock::now()),
		input_file_name(input_file_name), output_file_name(output_file_name),
		log_file_name("Logs.txt"), msg(log_msg){};
	void EndPoint();//For Writing into Logs any valuable information
	void UpdStartPointAndMessage(const std::string& log_msg);//For updating info message and recreating start point
private:
	system_clock::time_point start;
	std::string log_file_name;
	std::string input_file_name;
	std::string output_file_name;
	std::string msg;
};