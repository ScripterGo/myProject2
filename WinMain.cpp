
#include<iostream>
#include"../myProject2/wnd.h"
#include<windows.h>
#include<string>
#include<thread>
using namespace std;

void on_mb1_click(long long int* p) {
	window* wnd = reinterpret_cast<window*>(p);
	mouse* mouse = &wnd->mouse;
	wstring message = L"mouse button clicked!\n";
	wnd->console.log(message.c_str(), (int) message.size());
	
	wstring message2 = to_wstring(mouse->x_pos) + L" " + to_wstring(mouse->y_pos);
	wnd->set_title(message2);
}

void on_scroll(long long int* p) {
	window* wnd = reinterpret_cast<window*>(p);
	wstring message = L"scrolled once!";
	wnd->console.log(message.c_str(), (int) message.size());
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrev, LPSTR cmdLine, int displayMode) {
	window myWindow;
	myWindow.console.open();
	myWindow.create_window(hInstance, L"wnd1");
	myWindow.initiate_window(L"Did this work?");

	myWindow.mouse.lb_down.connect(on_mb1_click);
	myWindow.mouse.scroll_down.connect(on_scroll);

	window window_2;
	window_2.create_window(hInstance, L"wnd2");
	window_2.initiate_window(L"Second window?!");


	myWindow.initiate_message_loop();

	return 0;
}


