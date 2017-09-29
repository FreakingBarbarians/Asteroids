#pragma once
#include "GameObject.h"
class Wall : public GameObject
{
public:
	Wall();
	Wall(sf::VertexArray verts);
	void OnCollisionEnter2D(CollisionManifold & collision) override;
	void Update() override;
};

