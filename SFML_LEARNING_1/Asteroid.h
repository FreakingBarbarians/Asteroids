#pragma once
#include "GameObject.h"

class Asteroid : public GameObject{
public:
	Asteroid();
	Asteroid(sf::VertexArray);
	void setScale(sf::Vector2f scale);
	void setColor(sf::Color col);
	void OnCollisionEnter2D(CollisionManifold & collision) override;
	void Update() override;
};