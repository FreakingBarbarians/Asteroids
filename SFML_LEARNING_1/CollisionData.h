#pragma once
class GameObject;
struct AxisData {
	bool overlap;
	float magnitude;
	sf::Vector2f axis;
	AxisData() {
		overlap = false;
		magnitude = 0;
		sf::Vector2f axis;
	}
};

struct CollisionManifold {
	GameObject *object;
	bool collision;
	int contactPointCount;
	sf::Vector2f contactPoints[];
	CollisionManifold() {
		object = nullptr;
		collision = false;
		contactPointCount = 0;
		contactPoints;
	}
};