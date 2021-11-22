#pragma once

#include<chrono>

class ant_timer {

private:
	std::chrono::steady_clock::time_point last;
public:
	ant_timer();
	float mark();
	float peek();
};


