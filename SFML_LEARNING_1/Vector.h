#pragma once
#include "SFML\System.hpp"

class Vector {
public:
	static float dot(sf::Vector2f a, sf::Vector2f b) {
		return (a.x * b.x + a.y * b.y);
	}

	static sf::Vector2f normalize(const sf::Vector2f vector) {
		float length = sqrt((vector.x * vector.x) + (vector.y * vector.y));
		if (length != 0)
			return sf::Vector2f(vector.x / length, vector.y / length);
		else
			return vector;
	}
	
	static float DSquared(const sf::Vector2f A, const sf::Vector2f B) {
		sf::Vector2f C = A - B;
		return std::pow(C.x, 2) + std::pow(C.y, 2);
	}

	static float cross(const sf::Vector2f A, const sf::Vector2f B) {
		return A.x * B.y - B.x * A.y;
	}

};