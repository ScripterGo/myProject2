#pragma once
#include<memory>
#include<windows.h>
#include"keyboard.h"
#include"console.h"
#include"mouse.h"
#include"ant_timer.h"
#include"ant_exception.h"
#include"graphics.h"

class window {
	HWND handle = nullptr;
	WNDCLASSEX* desc = nullptr;
	bool should_quit = false;
public:
	keyboard keyboard;
	console console;
	mouse mouse;
	ant_timer timer;
	unique_ptr<graphics> p_graphics;

public:
	window() {};
	void create_window(HINSTANCE, const wchar_t* class_name);
	void initiate_window(LPCWSTR);
	void initiate_message_loop();
	void set_title(const wstring s) {
		SetWindowTextW(this->handle, reinterpret_cast<LPCWSTR>(s.c_str()));
	}
	void quit();
	bool process_messages();
	HWND get_handle();
	int do_frame();


private:
	static LRESULT CALLBACK wnd_proc(HWND, UINT, WPARAM, LPARAM);
	static LRESULT CALLBACK wnd_proc_initial(HWND, UINT, WPARAM, LPARAM);

};

