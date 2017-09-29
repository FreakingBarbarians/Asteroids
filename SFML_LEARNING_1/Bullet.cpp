#include "Bullet.h"

#include "Asteroid.h"
#include <iostream>
#include "DeltaTime.h"

Bullet::Bullet() {
	// always clockwise vertex declaration
	vertices.append(sf::Vector2f(0, 5));
	vertices.append(sf::Vector2f(0, 0));

	vertices.setPrimitiveType(sf::PrimitiveType::LineStrip);
	sf::Rect<float> bounds = vertices.getBounds();
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
	layer = 1;
}

void Bullet::setScale(sf::Vector2f scale) {
	Transformable::setScale(scale);
	radius = trueRadius * std::max(getScale().x, getScale().y);
}

void Bullet::setColor(sf::Color col) {
	for (int i = 0; i < vertices.getVertexCount(); i++) {
		vertices[i].color = col;
	}
}

void Bullet::Update() {
	sf::Vector2f pos = getPosition();
	sf::Vector2f temp = velocity;
	temp.x *= (DeltaTime::getDeltaTime().asSeconds());
	temp.y *= (DeltaTime::getDeltaTime().asSeconds());
	pos += temp;
	setPosition(pos);
}

// effects after physics simulation
void Bullet::OnCollisionEnter2D(CollisionManifold& collision) {
	if (collision.object->tag != 1) {
		collision.object->Destroy();
	}
	this->Destroy();
}