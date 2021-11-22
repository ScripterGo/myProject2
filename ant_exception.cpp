
#include"ant_exception.h"
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

string ant_exception::translate_error_code() const noexcept{
	char* buffer = nullptr;
	const DWORD res = FormatMessageA(
		FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS | FORMAT_MESSAGE_ALLOCATE_BUFFER,
		nullptr,
		this->hr,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		reinterpret_cast<LPSTR>(& buffer),
		0,
		nullptr
	);
	if (res == 0) {
		return "Unidentified Error Code";
	}
	string error_desc(buffer);
	LocalFree(buffer);
	return error_desc;
}

const char* ant_exception::what() const{
	ostringstream oss;
	oss << (this->get_type()).c_str() << endl << this->get_origin_string() << endl;
	oss << (this->translate_error_code()) << endl;
	this->buffer = oss.str();

	return this->buffer.c_str();
}

void ant_exception::message_popup() const noexcept{
	MessageBoxA(nullptr, this->what(), "ant_exception", MB_ICONEXCLAMATION | MB_OK);
}


#define ANT_EXCEPT(hr) 
