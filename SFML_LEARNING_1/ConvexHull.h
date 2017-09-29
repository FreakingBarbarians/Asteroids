#pragma once
#include "SFML\System.hpp"
#include "SFML\Graphics.hpp"
#include "Vector.h"
#include <iostream>
#include <list>
#include <stack>
#include "Window.h"


class ConvexHull {
public:
	static sf::VertexArray randomHullDebug(int radius) {
		sf::VertexArray points = sf::VertexArray();
		points.clear();

		int pointCount = (std::rand() % 15) + 3;

		for (int i = 0; i < pointCount; i++) {
			int x = std::rand() % radius - radius / 2;
			int y = std::rand() % radius - radius / 2;
			sf::Vector2f vert = sf::Vector2f(x, y);
			points.append(vert);
		}

		return convexHullDebug(points);

	}

	static sf::VertexArray convexHullDebug(sf::VertexArray points) {
		// Apply Graham's Algorithm

		sf::Vector2f min_y;
		int min_yi = -1;

		// find minimal y. Then order vertices based on polar angle
		for (int i = 0; i < points.getVertexCount(); i++) {
			if (min_yi == -1) {
				min_yi = i;
			}
			else {
				if (points[i].position.y < min_y.y) {
					min_y = points[i].position;
					min_yi = i;
				}
			}
		}

		// debug print
		// std::cout << "Source: [";

		//for (int i = 0; i < points.getVertexCount(); i++) {
		//	std::cout << "(" << points[i].position.x << " ," << points[i].position.y << ")";
		//}

		//std::cout << "]\n";

		//std::cout << "min_y: " << "(" << min_y.x << ", " << min_y.y << ") \n";

		std::list<sf::Vector2f> sortedVectors = std::list<sf::Vector2f>();
		sortedVectors.clear();
		std::list<float> sortedAngles = std::list<float>();
		sortedAngles.clear();

		// insertion sort on angle skipping over min_yi
		for (int i = 0; i < points.getVertexCount(); i++) {

			//std::cout << "Iteration:\n";

			if (i == min_yi) {
				// pass
				//std::cout << "pass \n";
			}
			else {
				sf::Vector2f vec = points[i].position - min_y;
				float angle = std::atan2f(vec.y, vec.x) * 180 / 3.141;
				//std::cout << "angle: " << angle << "\n";
				std::list<float>::iterator itf = sortedAngles.begin();
				std::list<sf::Vector2f>::iterator itv = sortedVectors.begin();
				//std::cout << "list: {";
				while (itf != sortedAngles.end() && angle > *itf) {
					//std::cout << "[(" << itv->x << ", " << itv->y << ") (" << *itf << ")]";
					++itf;
					++itv;
				}
				sortedVectors.insert(itv, points[i].position);
				sortedAngles.insert(itf, angle);
				//std::cout << "}";
			}
		}

		std::list<float>::iterator itf = sortedAngles.begin();
		std::list<sf::Vector2f>::iterator itv = sortedVectors.begin();
		//while (itf != sortedAngles.end()) {
		//	std::cout << "[(" << itv->x << ", " << itv->y << ") (" << *itf << ")]";
		//	++itf;
		//	++itv;
		//}

		//std::cout << "\n";

		// pruning
		itf = sortedAngles.begin();
		itv = sortedVectors.begin();
		while (itf != sortedAngles.end()) {
			std::list<float>::iterator tempf = ++itf;
			itf--;
			std::list<sf::Vector2f>::iterator tempv = ++itv;
			itv--;
			if (tempf != sortedAngles.end() && std::abs(*itf - *tempf) < 1) {
				float d1 = Vector::DSquared(min_y, *itv);
				float d2 = Vector::DSquared(min_y, *tempv);
				// delete nextnode
				if (d1 > d2) {
					// delete nodes until d2 > d1 or angle is different or reach end
					while (tempf != sortedAngles.end() && std::abs(*itf - *tempf) < 1 && Vector::DSquared(min_y, *itv) > Vector::DSquared(min_y, *tempv)) {
						tempf = sortedAngles.erase(tempf);
						tempv = sortedVectors.erase(tempv);
					}
				}
				// delete currnode
				else {
					itf = sortedAngles.erase(itf);
					itv = sortedVectors.erase(itv);
				}
			}
			else {
				itf++;
				itv++;
			}
		}

		itf = sortedAngles.begin();
		itv = sortedVectors.begin();
		while (itf != sortedAngles.end()) {
			std::cout << "[(" << itv->x << ", " << itv->y << ") (" << *itf << ")]\n";
			++itf;
			++itv;
		}

		if (sortedVectors.size() < 6) {
			return randomHullDebug(10); // recursive!
		}

		// Find outer hull

		std::stack<sf::Vector2f> hull = std::stack<sf::Vector2f>();

		while (!hull.empty()) {
			hull.pop();
		}

		sf::VertexArray pts = sf::VertexArray();
		itv = sortedVectors.begin();
		while (itv != sortedVectors.end()) {
			pts.append(*itv);
			itv++;
		}

		itv = sortedVectors.begin();

		sf::Vector2f bot = min_y;
		sf::Vector2f mid = *itv;
		sf::Vector2f top = *++itv;

		sf::VertexArray locked = sf::VertexArray();
		sf::VertexArray tmb = sf::VertexArray();

		tmb.setPrimitiveType(sf::PrimitiveType::Lines);
		locked.setPrimitiveType(sf::PrimitiveType::LinesStrip);

		while (itv != sortedVectors.end()) {
			tmb.clear();
			tmb.append(bot);
			tmb.append(mid);
			tmb.append(mid);
			tmb.append(top);
			tmb[0].color = sf::Color::Green;
			tmb[1].color = sf::Color::Green;
			tmb[2].color = sf::Color::Red;
			tmb[3].color = sf::Color::Red;
			sf::Vector2f bot2mid = mid - bot;
			sf::Vector2f bot2top = top - bot;

			std::cout << "\n bot:" << "(" << bot.x << ", " << bot.y << ")";
			std::cout << "\n mid:" << "(" << mid.x << ", " << mid.y << ")";
			std::cout << "\n top:" << "(" << top.x << ", " << top.y << ")";
			std::cout << "\n  bot2mid" << "(" << bot2mid.x << " ," << bot2mid.y << ")";
			std::cout << "\n  bot2top" << "(" << bot2top.x << " ," << bot2top.y << ")";

			if (Vector::cross(bot2mid, bot2top) >= 0) {
				std::cout << "\nleft";
				hull.push(bot);
				locked.append(bot);
				bot = mid;
				mid = top;
				top = *++itv;
			}
			else {
				std::cout << "\n right";
				if (!hull.empty()) {
					mid = bot;
					bot = hull.top();
					hull.pop();
					locked.resize(locked.getVertexCount() - 1);
				}
				else {
					mid = top;
					top = *++itv;
				}
			}

			sf::View CartesianView(sf::Vector2f(0, 0), sf::Vector2f(1920/50, -1080/50));
			Window::getInstance().window -> clear(sf::Color::Black);
			Window::getInstance().window -> setView(CartesianView);
			Window::getInstance().window->draw(locked);
			Window::getInstance().window->draw(tmb);
			Window::getInstance().window->draw(pts);
			Window::getInstance().window->display();
			std::cin.get();
		}
		hull.push(bot);
		hull.push(mid);
		hull.push(min_y);

		sf::VertexArray convexHull = sf::VertexArray();
		convexHull.setPrimitiveType(sf::PrimitiveType::LineStrip);
		while (!hull.empty()) {
			convexHull.append(hull.top());
			hull.pop();
		}

		sf::View CartesianView(sf::Vector2f(0, 0), sf::Vector2f(1920 / 50, -1080 / 50));
		Window::getInstance().window->clear(sf::Color::Black);
		Window::getInstance().window->setView(CartesianView);
		Window::getInstance().window->draw(convexHull);
		Window::getInstance().window->display();
		std::cin.get();

		return convexHull;
	}
};

// bugs are there :(