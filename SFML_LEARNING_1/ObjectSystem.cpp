#include "ObjectSystem.h"
#include <iostream>
#include "CollisionDetection.h"
#include "CollisionResolution.h"
#include "GameObject.h"

ObjectSystem::ObjectSystem() {
	items = std::unordered_map<int, LinkedNode*>();
	head = nullptr;
	toBeRemoved = std::list<void*>();
}

ObjectSystem& ObjectSystem::getInstance() {
	static ObjectSystem instance;
	return instance;
}

void ObjectSystem::add(GameObject& object) {

	LinkedNode* node = new LinkedNode(); // dynamic alloc?
	node->object = &object;
	if (head == nullptr) {
		head = node;
	} else {

		if (head->next != nullptr) {
			head->next->last = node;
		}
		node->next = head->next;
		head->next = node;
		node->last = head;
	}
	std::pair<int, LinkedNode*> item(object._id, node);
	items.insert(item);
}

void ObjectSystem::remove(GameObject& object) {
	LinkedNode * node = items[object._id];
	if (node->last != nullptr) {
		node->last->next = node->next;
		if (node->next != nullptr) {
			node->next->last = node->last;
		}
	}
	else {
		if (node->next != nullptr) {
			head = node->next;
		}
		else {
			head = nullptr;
		}
	}

	items.erase(object._id);
	// remove node next update
	toBeRemoved.push_front(node);
	toBeRemoved.push_front(&object);
}

void ObjectSystem::resolveCollisions() {
	LinkedNode * node = head;
	while (node != nullptr) {
		LinkedNode* next = node->next;
		while (next != nullptr) {
			CollisionManifold manifold;
			// some naughty hardcoding for collision layers
			if (node->object->layer == 1 && next->object->layer == 1){} 
			else if ((manifold = CollisionDetection::SAT(*node->object, *next->object)).collision) {
				// std::cout << " !collision! \n";
				// std::cin.get();
				// both sides of collision resolution
				manifold.object = next->object;
				node->object->OnCollisionEnter2D(manifold);
				manifold.object = node->object;
				next->object->OnCollisionEnter2D(manifold);
				
				CollisionResolution::Resolve2(*node->object, *next->object);

			}
			next = next->next;
		}
		node = node->next;
	}
}

void ObjectSystem::draw(sf::RenderWindow &window) {
	LinkedNode * p;
	p = head;
	while (p != nullptr) {
		window.draw(*p->object);
		p = p->next;
	}
}

void ObjectSystem::update() {

	for each (void* var in toBeRemoved)
	{
		delete var;
	}

	toBeRemoved.clear();
	
	LinkedNode * p = head;
	while (p != nullptr) {
		p->object->Update();
		p = p->next;
	}
}