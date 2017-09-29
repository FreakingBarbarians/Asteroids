#include "GameObject.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "ObjectSystem.h"
#include "IDDistributor.h"
#include "CollisionDetection.h"
void GameObject::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	states.transform *= getTransform();
	target.draw(vertices, states);
};

GameObject::GameObject() {
	_id = IDDistributor::getInstance().generateID();
	vertices = sf::VertexArray();
	radius = 0;
	trueRadius = 0;
	mass = 1;
	layer = 0;
	tag = 0;
}

void GameObject::Destroy() {
	ObjectSystem::getInstance().remove((*this));
}