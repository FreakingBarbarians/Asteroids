#include "FollowPointer.h"
#include <iostream>
#include "DeltaTime.h"
#include "Window.h"

FollowPointer::FollowPointer() {
	// always clockwise vertex declaration
	vertices.append(sf::Vector2f(0, 1));
	vertices.append(sf::Vector2f(0.5, -0.5));
	vertices.append(sf::Vector2f(-0.5, -0.5));
	vertices.append(sf::Vector2f(0, 1));

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
}

void FollowPointer::setScale(sf::Vector2f scale) {
	Transformable::setScale(scale);
}

void FollowPointer::setColor(sf::Color col) {
	for (int i = 0; i < vertices.getVertexCount(); i++) {
		vertices[i].color = col;
	}
}

void FollowPointer::OnCollisionEnter2D(CollisionManifold& collision) {
}

void FollowPointer::Update() {
	sf::Vector2f pos = (sf::Vector2f)sf::Mouse::getPosition(*Window::getInstance().window);
	pos.x -= Window::getInstance().window->getSize().x / 2;
	pos.y -= Window::getInstance().window->getSize().y / 2;
	pos.y = -pos.y;
	setPosition(pos);
}