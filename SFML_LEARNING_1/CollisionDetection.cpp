#include "CollisionDetection.h"
#include "Vector.h"
#include <limits>
#include <iostream>

inline AxisData axisOverlap(GameObject& a, GameObject& b, sf::Vector2f normal) {

	AxisData retVal = AxisData();
	retVal.overlap = false;

	int a_vert_max = a.vertices.getVertexCount();
	int b_vert_max = b.vertices.getVertexCount();

	sf::Vector2f a_max = a.getTransform().transformPoint(a.vertices[0].position);
	float a_maxf = 0;
	sf::Vector2f a_min = a.getTransform().transformPoint(a.vertices[0].position);
	float a_minf = 0;
	sf::Vector2f b_max = b.getTransform().transformPoint(b.vertices[0].position);
	float b_maxf = 0;
	sf::Vector2f b_min = b.getTransform().transformPoint(b.vertices[0].position);
	float b_minf = 0;

	bool a_set = false;
	bool b_set = false;
	
	for (int i = 0; i < std::max(a_vert_max, b_vert_max); i++) {
		// if there is a vertex in a
		if (i < a_vert_max) {
			// calculate the projection
			float result = Vector::dot(a.getTransform().transformPoint(a.vertices[i].position), normal);
			// set maximals accordingly
			if (result > a_maxf || !a_set) {
				a_maxf = result;
				a_max = a.vertices[i].position;
			}
			if (result < a_minf || !a_set) {
				a_minf = result;
				a_min = a.vertices[i].position;
			}
			a_set = true;
		}

		// same as above
		if (i < b_vert_max) {
			float result = Vector::dot(b.getTransform().transformPoint(b.vertices[i].position), normal);
			if (result > b_maxf || !b_set) {
				b_maxf = result;
				b_max = b.vertices[i].position;
			}
			if (result < b_minf || !b_set) {
				b_minf = result;
				b_min = b.vertices[i].position;
			}
			b_set = true;
		}
	}

	if (a_maxf < b_minf || b_maxf < a_minf) {
		// no overlap. SAT can early out
		return retVal;
	}
	else { 
		retVal.overlap = true;
		if (a_maxf >= b_minf) {
			retVal.magnitude = a_maxf - b_minf;
			retVal.axis = normal;
		}
		else { 
			retVal.magnitude = b_maxf - a_minf;
			retVal.axis = normal;
		}
		return retVal;
	}
}

CollisionManifold CollisionDetection::SAT(GameObject& a, GameObject& b) {
	// Collision Manifold Data
	CollisionManifold retVal = CollisionManifold();
	retVal.collision = false;

	// Seperating Axis Data
	AxisData MSA;
	bool MSA_SET = false;

	// check separation for a's planes
	for (int i = 0; i < a.vertices.getVertexCount() - 1; i++) {
		sf::Vector2f edge;

		// first vertex repeated at end

		edge = a.getTransform().transformPoint(a.vertices[i + 1].position) - a.getTransform().transformPoint(a.vertices[i].position);

		sf::Vector2f normal = sf::Vector2f(edge.y, -edge.x);

		AxisData axisData;
		
		
		if (!(axisData = axisOverlap(a, b, normal)).overlap) {
			// If There is no Overlap, Early out
			return retVal;
		}
		else {
			if (!MSA_SET || std::abs(axisData.magnitude) < std::abs(MSA.magnitude)) {
				// Otherwise check and set minimum seprating axis
				MSA = axisData;
				MSA_SET = true;
			}
		}
	}

	for (int i = 0; i < b.vertices.getVertexCount() - 1; i++) {

		sf::Vector2f edge;
		
		edge = b.getTransform().transformPoint(b.vertices[i + 1].position) - b.getTransform().transformPoint(b.vertices[i].position);
		
		sf::Vector2f normal = sf::Vector2f(edge.y, -edge.x);

		AxisData axisData;


		if (!(axisData = axisOverlap(a, b, normal)).overlap) {
			// If There is no Overlap, Early out
			return retVal;
		}
		else {
			if (!MSA_SET || std::abs(axisData.magnitude) < std::abs(MSA.magnitude)) {
				// Otherwise check and set minimum seprating axis
				MSA = axisData;
				MSA_SET = true;
			}
		}
	}
	retVal.collision = true;
	// std::cout << "\n MSA data:" << "\n magnitude: " << MSA.magnitude << "\n axis: (" << MSA.axis.x << ", " << MSA.axis.y << ")";
	return retVal;
};

