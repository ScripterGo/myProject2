
#include<iostream>
#include"keyboard.h"
#include"../myProject2/wnd.h"
#include<windows.h>
using namespace std;

HWND window::get_handle() {
	return this->handle;
}

void window::create_window(HINSTANCE hInstance, const wchar_t* class_name) {
	WNDCLASSEX* wc = new WNDCLASSEX({0});
	wc->hInstance = hInstance;
	wc->lpszClassName = L"main_window";
	wc->cbSize = sizeof(WNDCLASSEX);
	wc->hCursor = LoadCursorW(hInstance, IDC_ARROW);
	wc->hbrBackground = (HBRUSH) (COLOR_WINDOW + 2);
	wc->lpfnWndProc = this->wnd_proc;
	
	ATOM res = RegisterClassEx(wc);
	this->desc = wc;
}

void window::initiate_window(LPCWSTR window_name = L"my window") {
	if (this->desc == nullptr) RaiseException(1, EXCEPTION_NONCONTINUABLE, 0, NULL);

	WNDCLASSEX* wc = this->desc;
	HWND hwnd = CreateWindowEx(WS_EX_OVERLAPPEDWINDOW, wc->lpszClassName, window_name, WS_OVERLAPPEDWINDOW | WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, NULL, NULL);
	this->handle = hwnd;

	SetWindowLongPtrW(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));
	ShowWindow(hwnd, SW_SHOWDEFAULT);
}

void window::initiate_message_loop() {
	MSG msg = { 0 };
	while (GetMessageA(&msg, NULL, NULL, NULL) != 0) {
		TranslateMessage(&msg);
		DispatchMessageA(&msg);
		//if (flag == true) break;
	}
}

LRESULT CALLBACK window::wnd_proc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	window* my_window = reinterpret_cast<window*>(GetWindowLongPtrW(hwnd, GWLP_USERDATA));
	long long int* wnd_arg = reinterpret_cast<long long int*>(my_window);

	switch (msg) {
		case WM_CLOSE:
			PostQuitMessage(0); break;
		case WM_KEYDOWN:
			if ((lParam & (1u << 30)) > 0) {break;}
			my_window->keyboard.on_key_down((char)wParam, wnd_arg); break;
		case WM_KEYUP:
			my_window->keyboard.on_key_up((char)wParam, wnd_arg); break;
		case WM_MOUSEMOVE:
			my_window->mouse.on_mouse_move(wParam, lParam, wnd_arg); break;
		case WM_MBUTTONDOWN:
			my_window->mouse.on_mb_down(wnd_arg); break;
		case WM_MBUTTONUP:
			my_window->mouse.on_mb_up(wnd_arg); break;
		case WM_LBUTTONDOWN:
			my_window->mouse.on_lb_down(wnd_arg); break;
		case WM_LBUTTONUP:
			my_window->mouse.on_lb_up(wnd_arg); break;
		case WM_MOUSEWHEEL:
			my_window->mouse.on_scroll(wParam, wnd_arg); break;

	}
	return DefWindowProc(hwnd, msg, wParam, lParam);
}





