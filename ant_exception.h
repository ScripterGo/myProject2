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
	HRESULT hr;
public:
	ant_exception(HRESULT hr, int line, std::string file_name) : hr(hr), line(line), file_name(file_name) {};
	int get_line() const;
	std::string get_origin_string() const;
	std::string get_type() const;
	std::string translate_error_code() const noexcept;
	const std::string& get_file_name() const;
	const char* what() const override;
	void message_popup() const noexcept;
};


#define throw_ant(hr) ant_exception e(hr, __LINE__, __FILE__); e.message_popup();
#define throw_ant_if(hr) if(FAILED(hr)){throw_ant(hr)}
