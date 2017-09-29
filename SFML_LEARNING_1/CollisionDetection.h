#pragma once
#include "SFML\System.hpp"
#include "SFML\Graphics.hpp"
#include "CollisionData.h"
#include "GameObject.h"

class CollisionDetection {
public:
	static CollisionManifold SAT(GameObject& a, GameObject& b);
};