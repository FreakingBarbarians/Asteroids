#include "Wall.h"

Wall::Wall() {
	// always clockwise vertex declaration
	vertices.append(sf::Vector2f(0, 100));

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
	layer = 0;
	tag = 1;
	mass = 400;
}

Wall::Wall(sf::VertexArray verts) {
	// always clockwise vertex declaration
	vertices = verts;
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
	layer = 0;
	tag = 1;
	mass = 10000;
}

void Wall::Update() {
}

void Wall::OnCollisionEnter2D(CollisionManifold& collision) {
}