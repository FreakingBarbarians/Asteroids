#include "Ship.h"
#include <iostream>
#include "DeltaTime.h"
#include "Window.h"
#include "Bullet.h"
#include "Vector.h"
#include "ObjectSystem.h"

Ship::Ship() {
	// always clockwise vertex declaration
	vertices.append(sf::Vector2f(0, 1));
	vertices.append(sf::Vector2f(0.5, -0.5));
	vertices.append(sf::Vector2f(-0.5, -0.5));
	vertices.append(sf::Vector2f(0, 1));

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
	layer = 1;
}

void Ship::setScale(sf::Vector2f scale) {
	Transformable::setScale(scale);
}

void Ship::setColor(sf::Color col) {
	for (int i = 0; i < vertices.getVertexCount(); i++) {
		vertices[i].color = col;
	}
}

void Ship::OnCollisionEnter2D(CollisionManifold& collision) {
}

void Ship::Fire() {
	if (coolDown <= 0) {
		coolDown = fireTime;
		// fire code;

		sf::Vector2f mouse = (sf::Vector2f)sf::Mouse::getPosition(*Window::getInstance().window);
		mouse.x -= Window::getInstance().window->getSize().x / 2;
		mouse.y -= Window::getInstance().window->getSize().y / 2;
		mouse.y = -mouse.y;
		sf::Vector2f toMouse = mouse - getPosition();
		sf::Vector2f normal = Vector::normalize(toMouse);
		
		normal.x *= 100;
		normal.y *= 100;

		Bullet* bullet = new Bullet();
		bullet->setPosition(getTransform().transformPoint(sf::Vector2f(0, 1)));
		bullet->setRotation(getRotation());
		bullet->velocity = normal;
		ObjectSystem::getInstance().add(*bullet);
	}
}

void Ship::Update() {
	// input
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		velocity.x *= (1 - DeltaTime::getInstance().getDeltaTime().asSeconds());
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		velocity.x += -100 * DeltaTime::getInstance().getDeltaTime().asSeconds();
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		velocity.x += 100 * DeltaTime::getInstance().getDeltaTime().asSeconds();
	}
	else {
		velocity.x *= (1 - DeltaTime::getInstance().getDeltaTime().asSeconds());
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		velocity.y *= (1 - DeltaTime::getInstance().getDeltaTime().asSeconds());
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		velocity.y += -100 * DeltaTime::getInstance().getDeltaTime().asSeconds();
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		velocity.y += 100 * DeltaTime::getInstance().getDeltaTime().asSeconds();
	}
	else {
		velocity.y *= (1 - DeltaTime::getInstance().getDeltaTime().asSeconds());
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
		Fire();
	}

	sf::Vector2f mouse = (sf::Vector2f)sf::Mouse::getPosition(*Window::getInstance().window);
	mouse.x -= Window::getInstance().window->getSize().x / 2;
	mouse.y -= Window::getInstance().window->getSize().y / 2;
	mouse.y = -mouse.y;

	sf::Vector2f toMouse = mouse - getPosition();
	
	coolDown = coolDown - DeltaTime::getInstance().getDeltaTime().asSeconds();

	float rads = std::atan2f(toMouse.y, toMouse.x);
	float deg = (180 / 3.141592653 )* rads;
	// std::cout << rads << "|" << deg << "\n";
	setRotation(deg -90);
	sf::Vector2f pos = getPosition();
	sf::Vector2f temp = velocity;
	temp.x *= (DeltaTime::getDeltaTime().asSeconds());
	temp.y *= (DeltaTime::getDeltaTime().asSeconds());
	pos += temp;
	setPosition(pos);
}