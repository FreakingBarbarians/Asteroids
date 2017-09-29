#pragma once
#include <queue>

// Singleton
// Generates and distributes id's for gameObjects
// When a gameobject is destroyed the id needs to be released manually
class IDDistributor {
public:
	std::queue<int> queue;
	int generateID(); // get the next id, making it unusable by other objects
	void returnID(int id); // return the id making it usable by future objects
	int peekID(); // see what the next id will be without making it unusable by other objects
	static IDDistributor & getInstance(); // get the instance of the IDDistributor
private:
	// Some singleton stuff
	IDDistributor();
	IDDistributor(IDDistributor const&);      // Don't Implement.
	void operator=(IDDistributor const&);		  // Don't implement
};