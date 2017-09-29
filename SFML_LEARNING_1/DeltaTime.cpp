#include "DeltaTime.h"
#include <iostream>

DeltaTime::DeltaTime() {
	clock = sf::Clock();
	clock.restart();
}

DeltaTime& DeltaTime::getInstance() {
	static DeltaTime instance; // initializes the first time the function runs
							   // stays initialized for rest of the calls
							   // Future calls will reference this instance
							   // Scope is whole program
	return instance;
}

sf::Time& DeltaTime::getDeltaTime() {
	static sf::Time dt;
	return dt;
}