#pragma once
#include "GameObject.h"
class FollowPointer : public GameObject {
public:
	FollowPointer();
	void setScale(sf::Vector2f scale);
	void setColor(sf::Color col);
	void OnCollisionEnter2D(CollisionManifold & collision) override;
	void Update() override;
};