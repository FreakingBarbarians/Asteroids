#pragma once
#include "SFML\System.hpp"
#include "SFML\Graphics.hpp"

// Ahh singletons :)
class Window {
public:
	sf::RenderWindow* window;
	static Window& getInstance();
private:
	Window();
	void operator=(sf::RenderWindow const&); // Don't implement
};