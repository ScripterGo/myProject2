#pragma once
#include<windows.h>
#include<bitset>
#pragma once
#include<vector>
#include"event.h"
using namespace std;

class keyboard {
	bitset<256> down;
	void on_key_down(const char& c, long long int* p);
	void on_key_up(const char& c, long long int* p);
	vector<event> down_events, up_events;

public:
	keyboard() { 
		down_events.assign(256, event());
		up_events.assign(256, event());
	}

	connection* to_key_down(const char& c, void(*funcPtr) (long long int* p));
	connection* to_key_up(const char& c, void(*funcPtr) (long long int* p));
	bool is_down(const char& c);


	friend class window;
};


