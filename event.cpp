#include"event.h"
using namespace std;

void event::fire(long long int* arg) {
	for (const connection c : this->connections) {
		c.execute(arg);
	}
}

connection* event::connect(void (*funcPtr) (long long int* arg)) {
	connection new_connection = connection(funcPtr);
	this->connections.push_back(new_connection);

	connection& in_container = this->connections[this->connections.size() - 1];
	in_container.parent_event = reinterpret_cast<void*>(this);
	return &in_container;
}

void event::disconnect_connection(connection* cnnct) {
	for (auto it = this->connections.begin(); it != this->connections.end(); it++) {
		if ((*it) == (*cnnct)) {
			this->connections.erase(it); break;
		}
	}
}

void event::disconnect_all() {
	this->connections.clear();
	this->connections.resize(0);
}


