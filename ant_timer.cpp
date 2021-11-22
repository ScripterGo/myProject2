
#include<chrono>
#include"ant_timer.h"

#include<windows.h>
using namespace std;
using namespace chrono;


ant_timer::ant_timer() {
	this->last = steady_clock::now();
	OutputDebugStringA("It has been initialized!");
}

float ant_timer::mark() {
	auto curr = steady_clock::now();
	const duration<float> delta = curr - this->last;
	this->last = curr;
	return delta.count();
}

float ant_timer::peek() {
	auto curr = steady_clock::now();
	return duration<float>( curr - (this->last) ).count();
}

