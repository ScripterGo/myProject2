
#include"connection.h"
#include"event.h"
using namespace std;

void connection::execute(long long int* arg) const{
	this->funcPtr(arg);
}

bool connection::operator==(const connection& ot) {
	return (& ot) == ( & (*this));
}

void connection::disconnect() {
	if (this->parent_event == nullptr) return;
	event* e = reinterpret_cast<event*>(this->parent_event);
	e->disconnect_connection(this);
}