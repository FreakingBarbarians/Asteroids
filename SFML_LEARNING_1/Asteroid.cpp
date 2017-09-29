#include "Asteroid.h"
#include <iostream>
#include "DeltaTime.h"
Asteroid::Asteroid(){
	// always clockwise vertex declaration
	vertices.append(sf::Vector2f(-1, -1));
	vertices.append(sf::Vector2f(-1, 1));
	vertices.append(sf::Vector2f(1, 1));
	vertices.append(sf::Vector2f(1, -1));
	vertices.append(sf::Vector2f(-1, -1));

	vertices.setPrimitiveType(sf::PrimitiveType::LineStrip);
	sf::Rect<float> bounds = vertices.getBounds();
	trueRadius = std::max(bounds.width, bounds.height)/2;
	int i = 0;
	float x = 0, y = 0;
	while (i < vertices.getVertexCount()) {
		x += vertices[i].position.x;
		y += vertices[i].position.y;
		i++;
	}
	x = x / i;
	y = y / i;
	setOrigin(x, y);
	layer = 0;
}

Asteroid::Asteroid(sf::VertexArray verts) {
	vertices = verts;

	vertices.setPrimitiveType(sf::PrimitiveType::LineStrip);
	sf::Rect<float> bounds = vertices.getBounds();
	trueRadius = std::max(bounds.width, bounds.height) / 2;
	int i = 0;
	float x = 0, y = 0;
	while (i < vertices.getVertexCount()) {
		x += vertices[i].position.x;
		y += vertices[i].position.y;
		i++;
	}
	x = x / i;
	y = y / i;
	setOrigin(x, y);
	layer = 0;
}

void Asteroid::setScale(sf::Vector2f scale) {
	Transformable::setScale(scale);
	radius = trueRadius * std::max(getScale().x, getScale().y);
}

void Asteroid::setColor(sf::Color col) {
	for (int i = 0; i < vertices.getVertexCount(); i++) {
		vertices[i].color = col;
	}
}

void Asteroid::Update() {
	sf::Vector2f pos = getPosition();
	sf::Vector2f temp = velocity;
	temp.x *= (DeltaTime::getDeltaTime().asSeconds());
	temp.y *= (DeltaTime::getDeltaTime().asSeconds());
	pos += temp;
	setPosition(pos);
}

// effects after physics simulation
void Asteroid::OnCollisionEnter2D(CollisionManifold& collision) {
}