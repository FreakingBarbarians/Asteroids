#pragma once
#include "SFML\Main.hpp"
#include "SFML\System.hpp"
#include "SFML\Graphics.hpp"
#include "IDDistributor.h"
#include "CollisionData.h"
#include <math.h>

class GameObject : public sf::Drawable, public sf::Transformable
{
// position/rotation/scale comes from transformable
// vertices define points of a closed polygon that will be outlined
// velocity is the direction and speed the object is moving in pixels;

public:
	sf::VertexArray vertices;
	sf::Vector2f velocity;
	int _id; // should never be changed ever!!
	int layer; // collision layer. sorta?
	int tag; // tag
	virtual void Update() {}; // Updates the game state of the object
	virtual void Destroy(); // sends message to Objectsystem, called on destruction
	virtual void OnCollisionEnter2D(CollisionManifold & collision) {}; // some borrowed ideas from Unity :)
	float radius; // transformed radius bounding circle
	float mass; // mass of object
	GameObject();
private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
protected:
	float trueRadius; // untransformed radius bounding circle
};