
#include<windows.h>
#include<windowsx.h>
#include"mouse.h"
#include"definitions.h"
using namespace std;

void mouse::on_mouse_move(WPARAM wParam, LPARAM lParam, event_arg p) {
	this->x_pos = GET_X_LPARAM(lParam);
	this->y_pos = GET_Y_LPARAM(lParam);
	this->mouse_moved.fire(p);
}

void mouse::on_mb_down(event_arg p) {
	this->is_mb_down = true;
	this->mb_down.fire(p);
}

void mouse::on_mb_up(event_arg p) {
	this->is_mb_down = false;
	this->mb_up.fire(p);
}

void mouse::on_lb_down(event_arg p) {
	this->is_lb_down = true;
	this->lb_down.fire(p);
}

void mouse::on_lb_up(event_arg p) {
	this->is_lb_down = false;
	this->lb_up.fire(p);
}

void mouse::on_scroll(WPARAM wParam, event_arg p) {
	int t = GET_WHEEL_DELTA_WPARAM(wParam) / this->scroll_threshold;
	for (int i = 0; i < abs(t); i++) {
		if (t > 0) {
			this->scroll_up.fire(p);
		}
		else {
			this->scroll_down.fire(p);
		}
	}
}


