#pragma once
#include "GameObject.h"

class Ship : public GameObject {
public:

	float fireTime = 0.5f;
	float coolDown = 0;
	Ship();
	void setScale(sf::Vector2f scale);
	void setColor(sf::Color col);
	void OnCollisionEnter2D(CollisionManifold & collision) override;
	void Update() override;
	void Fire();
};

