#include "IDDistributor.h"
#include <iostream>
IDDistributor::IDDistributor() {
	queue = std::queue<int>();
	queue.empty();
	// Rather simplistic, but we simply load 5000 int values into the queue.
	for (int i = 0; i < 5000; i++) {
		queue.push(i);
	}
}

IDDistributor & IDDistributor::getInstance() {
	static IDDistributor instance = IDDistributor();
	return instance;
}

int IDDistributor::generateID() {
	int id = queue.front();
	queue.pop();
	return id;
}

void IDDistributor::returnID(int id) {
	queue.push(id);
}

int IDDistributor::peekID() {
	return queue.front();
}