#pragma once
#include "GameObject.h"
#include "SFML\System.hpp"

class CollisionResolution{
public:
	static void Resolve1(GameObject& a, GameObject& b) {

		float a_mass = a.mass;
		sf::Vector2f a_vel = a.velocity;

		float b_mass = b.mass;
		sf::Vector2f b_vel = b.velocity;

		a.velocity.x = b_vel.x * b_mass / a_mass;
		a.velocity.y = b_vel.y * b_mass / a_mass;
		b.velocity.x = a_vel.x * a_mass / b_mass;
		b.velocity.y = a_vel.y * a_mass / b_mass;
	}

	static void Resolve2(GameObject& a, GameObject& b) {

		sf::Vector2f a_vel = a.velocity;

		sf::Vector2f b_vel = b.velocity;
		
		a.velocity.x = ((a.mass - b.mass) / (a.mass + b.mass)) * a_vel.x + ((2 * b.mass) / (a.mass + b.mass)) * b_vel.y;
		a.velocity.y = ((a.mass - b.mass) / (a.mass + b.mass)) * a_vel.y + ((2 * b.mass) / (a.mass + b.mass)) * b_vel.y;
		b.velocity.x = ((b.mass - a.mass) / (b.mass + a.mass)) * b_vel.x + ((2 * a.mass) / (b.mass + a.mass)) * a_vel.x;
		b.velocity.y = ((b.mass - a.mass) / (b.mass + a.mass)) * b_vel.y + ((2 * a.mass) / (b.mass + a.mass)) * a_vel.y;
	}
};