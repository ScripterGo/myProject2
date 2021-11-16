#pragma once
#include<vector>
#include"connection.h"
using namespace std;

class event {
	vector<connection> connections;
	
public:
	void fire(long long int* arg=nullptr);
	event() {};
	connection* connect(void (*funcPtr)(long long int* arg));
	void disconnect_all();
	void disconnect_connection(connection* cnnct);
	friend class vector<connection>;
};