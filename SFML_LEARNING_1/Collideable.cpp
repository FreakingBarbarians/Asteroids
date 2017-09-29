//#include "Collideable.h"
//
//Collideable::Collideable() {
//	radius = 0;
//	trueRadius = 0;
//}
//
//bool Collideable::colliding(Collideable& other) {
//	sf::Vector2f thisVec = getPosition();
//	sf::Vector2f thatVec = other.getPosition();
//
//	float dmag = pow((thisVec.x - thatVec.x), 2) + pow((thisVec.y - thatVec.y), 2); // square of the distance
//	if (dmag <= pow(radius, 2) + pow(other.radius, 2)) {
//		// if square of the distance is less than square of combined radii 
//		return true;
//	}
//	return false;
//}