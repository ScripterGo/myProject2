
#include<iostream>
#include"keyboard.h"
#include"wnd.h"
#include"graphics.h"
#include<windows.h>
#include<sstream>
#include"shapes.h"

const float PI = 3.14159f;

using namespace std;

HWND window::get_handle() {
	return this->handle;
}

void window::quit() {
	this->should_quit = true;
}

void window::create_window(HINSTANCE hInstance, const wchar_t* class_name) {
	WNDCLASSEX* wc = new WNDCLASSEX({0});
	wc->hInstance = hInstance;
	wc->lpszClassName = L"main_window";
	wc->cbSize = sizeof(WNDCLASSEX);
	wc->hCursor = LoadCursorW(hInstance, IDC_ARROW);
	wc->hbrBackground = (HBRUSH) (COLOR_WINDOW + 2);
	wc->lpfnWndProc = this->wnd_proc_initial;
	ATOM res = RegisterClassEx(wc);
	this->desc = wc;
}

void window::initiate_window(LPCWSTR window_name = L"my window") {
	if (this->desc == nullptr) RaiseException(1, EXCEPTION_NONCONTINUABLE, 0, NULL);

	RECT rc = { 0 };
	rc.left = 300;
	rc.right = 900;
	rc.top = 300;
	rc.bottom = 900;
	AdjustWindowRectEx(&rc, WS_OVERLAPPEDWINDOW, false, 0);

	WNDCLASSEX* wc = this->desc;
	HWND hwnd = CreateWindowEx(WS_EX_OVERLAPPEDWINDOW, wc->lpszClassName, window_name, WS_OVERLAPPEDWINDOW | WS_VISIBLE, rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top, NULL, NULL, NULL, this);
	this->p_graphics = unique_ptr<graphics>(new graphics(hwnd));
	ShowWindow(hwnd, SW_SHOWDEFAULT);
}

bool window::process_messages() {
	MSG msg;
	while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
		if (msg.message == WM_QUIT) {
			return false;
		}
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return true;
}

void window::initiate_message_loop() {
	int fps = 60;
	DWORD dur = UINT((1.0 / float(fps)) * 1000.0);
	while (true) {
		bool res = this->process_messages();
		if (res == false) return;
		this->do_frame();
		Sleep(dur);
	}
}

int window::do_frame() {
	float curr_t = this->timer.peek();
	wostringstream oss;
	oss << L"The current elapsed time is: " << curr_t;
	this->set_title(oss.str());

	float inc = 2.0f * PI / 3.0f;
	std::vector<float> angles = {
		0.0,
		inc,
		inc * 2.0f
	};

	static cube t(0.0f, 0.0f, 150.0f, 100.0f);

	if (this->keyboard.is_down('D')) {
		t.rotate_y(10.0f / 60.0f);
	};
	if (this->keyboard.is_down('S')) {
		t.rotate_x(1.0f / 60.0f);
	}
	this->p_graphics->render_cube(t);

	this->p_graphics->end_frame();
	return 0;
}

LRESULT CALLBACK window::wnd_proc_initial(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	if(msg == WM_CREATE){
		const CREATESTRUCTW* const info = reinterpret_cast<CREATESTRUCTW*>(lParam);
		window* wnd = reinterpret_cast<window*>(info->lpCreateParams);
 		wnd->handle = hwnd;
		SetWindowLongPtrW(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(wnd));
		SetWindowLongPtrW(hwnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(window::wnd_proc));
	}
	return DefWindowProc(hwnd, msg, wParam, lParam);
}
int cnt = 0;
LRESULT CALLBACK window::wnd_proc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	window* my_window = reinterpret_cast<window*>(GetWindowLongPtrW(hwnd, GWLP_USERDATA));
	long long int* wnd_arg = reinterpret_cast<long long int*>(my_window);
	cnt++;
	//OutputDebugStringA(to_string(cnt).append("\n").c_str());
	
	switch (msg) {
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





