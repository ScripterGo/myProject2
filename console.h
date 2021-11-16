#pragma once

#include<windows.h>
using namespace std;

class console {
	HANDLE Chnd = nullptr;

public:
	void open();
	void close();
	void log(const wchar_t* str, unsigned int n);
	void log(int a);

};
