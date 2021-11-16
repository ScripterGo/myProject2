
#include<windows.h>
#include"console.h"
using namespace std;


void console::log(const wchar_t* str, unsigned int n) {
	if (this->Chnd == nullptr) RaiseException(2, EXCEPTION_CONTINUE_EXECUTION, 0, NULL);
	WriteConsoleW(this->Chnd, reinterpret_cast<const void*>(str), n, 0, NULL);
}

void console::log(int a) {
	if (this->Chnd == nullptr) RaiseException(2, EXCEPTION_CONTINUE_EXECUTION, 0, NULL);
	wchar_t str[32]; unsigned short int n = 0;
	bool is_negative = (a < 0);
	if (is_negative) a = -a;

	while (a != 0) {
		int c = a % 10;
		str[n] = c + '0';
		a = (a - c) / 10;
		n++;
	}
	if (is_negative == true) {str[n] = '-'; n++;}

	wchar_t res[32];
	for (int i = n - 1; i >= 0; i--) res[n - 1 - i] = str[i];
	WriteConsoleW(this->Chnd, reinterpret_cast<const void*>(res), n, 0, NULL);
}

void console::open() {
	if (this->Chnd != nullptr) this->close();
	AllocConsole();
	this->Chnd = GetStdHandle(STD_OUTPUT_HANDLE);
}

void console::close() {
	CloseHandle(this->Chnd);
}

