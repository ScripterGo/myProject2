#pragma once
using namespace std;

class connection {
	void (*funcPtr) (long long int* arg) = nullptr;
	void* parent_event = nullptr; //Should be a pointer to an event_type

public:
	connection() {};
	connection(void (*funcPtr) (long long int* arg)) : funcPtr(funcPtr){};
	void execute(long long int* arg) const;
	bool operator==(const connection& other);
	void disconnect();

	friend class event;
};
