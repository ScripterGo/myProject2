
#include"ant_exception.h";
#include<windows.h>
#include<string>
#include<sstream>
using namespace std;

int ant_exception::get_line() const{
	return this->line;
}

const string& ant_exception::get_file_name() const{
	return this->file_name;
}

string ant_exception::get_type() const{
	return string("Ant Exception");
}

string ant_exception::get_origin_string() const{
	ostringstream oss;
	oss << "[File] " << this->file_name << endl;
	oss << "[Line] " << this->line << endl;
	return oss.str();
}

const char* ant_exception::what() const{
	ostringstream oss;
	oss << (this->get_type()).c_str() << endl << this->get_origin_string();
	this->buffer = oss.str();
	return this->buffer.c_str();
}

