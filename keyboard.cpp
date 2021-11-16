
#include<Windows.h>
#include"keyboard.h"
using namespace std;



void keyboard::on_key_down(const char& c, long long int* p = nullptr) {
	this->down[c] = true;
	this->down_events[c].fire(p);
}

void keyboard::on_key_up(const char& c, long long int* p = nullptr) {
	this->down[c] = false;
	this->up_events[c].fire(p);
}

connection* keyboard::to_key_down(const char& c, void(*funcPtr)(long long int* p)) {
	return this->down_events[c].connect(funcPtr);
}

connection* keyboard::to_key_up(const char& c, void(*funcPtr)(long long int* p)) {
	return this->up_events[c].connect(funcPtr);
}

bool keyboard::is_down(const char& c) { return this->down[c]; }
