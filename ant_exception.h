#pragma once

#include<exception>
#include<Windows.h>
#include<string>

class ant_exception : public std::exception {
private:
	std::string note;
	mutable std::string buffer;
	int line;
	std::string file_name;
public:
	ant_exception(int line, std::string file_name) : line(line), file_name(file_name) {};
	int get_line() const;
	std::string get_origin_string() const;
	std::string get_type() const;
	const std::string& get_file_name() const;
	const char* what() const override;
};


#define throw_ant(__)
