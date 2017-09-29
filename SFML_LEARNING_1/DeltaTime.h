#pragma once
#include "SFML\System.hpp"
class DeltaTime
{
public:
	sf::Clock clock;
	static DeltaTime& getInstance();
	static sf::Time& getDeltaTime();
private:
	DeltaTime();
	DeltaTime(DeltaTime const&);      // Don't Implement.
	void operator=(DeltaTime const&); // Don't implement
};