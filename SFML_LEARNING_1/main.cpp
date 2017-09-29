#include <SFML/Graphics.hpp>
#include "Asteroid.h"
#include "Ship.h"
#include "DeltaTime.h"
#include "ObjectSystem.h"
#include <iostream>
#include <cstdlib>
#include "Window.h"
#include "FollowPointer.h"
#include "Wall.h"
#include "ConvexHull.h"

// make a singleton DeltaTime Clock
int main()
{
	sf::RenderWindow& window = *Window::getInstance().window;
	// Game Objects work in Cartesian Coords. The only difference between the two is the invertex
	// Y axis. so we make our camera look upside down by passing -y value.
	// We also want the center of our camera to be (0,0) so this is the first argument
	sf::View CartesianView(sf::Vector2f(0, 0), sf::Vector2f(1920, -1080));
	ObjectSystem& cs = ObjectSystem::getInstance();
	
	// Asteroid Spawning

	for (int i = 0; i < 50; i++) {
		Asteroid* aster = new Asteroid(ConvexHull::randomHullDebug(10));
		aster->setPosition(sf::Vector2f(std::rand() % 1000 - 500, std::rand() % 1000 - 500));
		aster->setScale(sf::Vector2f(5, 5));
		aster->mass = std::pow(aster->getScale().x,2) + std::pow(aster->getScale().y,2);
		aster->setRotation(std::rand() % 360);
		aster->velocity = sf::Vector2f(std::rand() % 20 - 10, std::rand() % 20 - 10);
		ObjectSystem::getInstance().add(*aster);
	}

	Ship* player = new Ship();
	player->setScale(sf::Vector2f(10, 10));
	player->mass = 40;
	player->setRotation(0);
	ObjectSystem::getInstance().add(*player);

	float width = window.getSize().x;
	float height = window.getSize().y;

	sf::VertexArray v1 = sf::VertexArray();
	v1.clear();
	v1.append(sf::Vector2f(0, 0));
	v1.append(sf::Vector2f(width, 0));
	Wall* w_north = new Wall(v1);
	w_north->setPosition(0, height/2);

	sf::VertexArray v2 = sf::VertexArray();
	v2.clear();
	v2.append(sf::Vector2f(0, 0));
	v2.append(sf::Vector2f (width, 0));
	Wall* w_south = new Wall(v2);
	w_south->setPosition(0, -height / 2);

	sf::VertexArray v3 = sf::VertexArray();
	v3.clear();
	v3.append(sf::Vector2f(0, 0));
	v3.append(sf::Vector2f(0, height));
	Wall* w_east = new Wall(v3);
	w_east->setPosition(-width / 2, 0);

	sf::VertexArray v4 = sf::VertexArray();
	v4.clear();
	v4.append(sf::Vector2f(0, 0));
	v4.append(sf::Vector2f(0, height));
	Wall* w_west = new Wall(v4);
	w_west->setPosition(width / 2, 0);

	ObjectSystem::getInstance().add(*w_north);
	ObjectSystem::getInstance().add(*w_east);
	ObjectSystem::getInstance().add(*w_south);
	ObjectSystem::getInstance().add(*w_west);
	
	while (window.isOpen()) {
		sf::Event e;
		if (window.pollEvent(e)) {
			if (e.type == sf::Event::Closed) {
				window.close();
			}
		}

		// Set View and Clear
		window.clear(sf::Color::Black);
		window.setView(CartesianView);
		
		// Game Logic + Drawing
		ObjectSystem::getInstance().update();
		ObjectSystem::getInstance().resolveCollisions();
		ObjectSystem::getInstance().draw(window);

		// Display
		window.display();

		// Reset Clock
		// std::cin.get();
		DeltaTime::getDeltaTime() = (DeltaTime::getInstance()).clock.restart();
	}
	return 0;
}