#pragma once
#include <stdlib.h>
#include <unordered_map>
#include <list>
#include "GameObject.h"

// also assigns id's?
class ObjectSystem {
	// container for accessing objects
	struct LinkedNode {
		GameObject* object;
		LinkedNode* next;
		LinkedNode* last;
		LinkedNode() {
			object = nullptr;
			next = nullptr;
			last = nullptr;
		}
	} node;

public:
	LinkedNode* head;
	static ObjectSystem & getInstance();
	void add(GameObject& object); // adds an object to the system
	void remove(GameObject& object); // removes an object from the system
	void resolveCollisions(); // finds collisions and resolves them
	void draw(sf::RenderWindow &window); // draws objects on screen
	void update();
	std::unordered_map<int, LinkedNode*> items;
private:
	std::list<void*> toBeRemoved;
	ObjectSystem();
	ObjectSystem(ObjectSystem const&);      // Don't Implement, should never have object system to set from
	void operator=(ObjectSystem const&);	// Don't implement, should never have object system to equate to
};