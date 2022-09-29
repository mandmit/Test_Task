#include "Logger.h"
#pragma warning(disable : 4996) //disable warning about std::ctime()
void Logger::UpdStartPointAndMessage(const std::string& log_msg) {
	start = system_clock::now();
	msg = log_msg;
}

void Logger::EndPoint() {
	auto end = system_clock::now();
	auto duration = end - start;
	std::time_t end_work = system_clock::to_time_t(end);
	std::ofstream f_stream;
	f_stream.open(log_file_name, std::ios::app);
	f_stream << "Working with input file with name: " << input_file_name << ' '
		<< " and output file with name: " << output_file_name << " Time: " << std::ctime(&end_work) << "\tInformation: ";
	f_stream << msg << ": " << duration_cast<milliseconds>(duration).count() << " ms\n" << '\n';
	f_stream.close();
}