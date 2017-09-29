#pragma once
#include "GameObject.h"
class Bullet : public GameObject {
public:
	Bullet();
	void setScale(sf::Vector2f scale);
	void setColor(sf::Color col);
	void OnCollisionEnter2D(CollisionManifold & collision) override;
	void Update() override;
};