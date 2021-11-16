
#include<windows.h>
#include"event.h"
#include"definitions.h"

class mouse {
	void on_mouse_move(WPARAM wParam, LPARAM lParam, event_arg);
	void on_mb_down(event_arg); void on_mb_up(event_arg);
	void on_lb_down(event_arg); void on_lb_up(event_arg);
	void on_scroll(WPARAM wParam, event_arg);
public:
	unsigned short x_pos = 0, y_pos = 0;
	event mouse_moved;
	event mb_down, mb_up;
	event lb_down, lb_up;
	event scroll_up, scroll_down;

	bool is_mb_down = false;
	bool is_lb_down = false;
	unsigned short scroll_threshold = 120;
	friend class window;
};
