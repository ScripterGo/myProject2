#pragma once
#include<windows.h>
#include"keyboard.h"
#include"console.h"
#include"mouse.h"

class window {
	HWND handle = nullptr;
	WNDCLASSEX* desc = nullptr;
public:
	keyboard keyboard;
	console console;
	mouse mouse;

public:
	window() {};
	void create_window(HINSTANCE, const wchar_t* class_name);
	void initiate_window(LPCWSTR);
	void initiate_message_loop();
	void set_title(const wstring s) {
		SetWindowTextW(this->handle, s.c_str());
	}
	HWND get_handle();



private:
	static LRESULT CALLBACK wnd_proc(HWND, UINT, WPARAM, LPARAM);

};

