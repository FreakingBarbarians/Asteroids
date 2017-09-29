#pragma once
#include "SFML\System.hpp"
class Transform {
public:
	sf::Vector2f pos;
	sf::Vector2f rotation;
	sf::Vector2f scale;
	sf::Vector2f up; // read only
	sf::Vector2f right;

	Transform();
};