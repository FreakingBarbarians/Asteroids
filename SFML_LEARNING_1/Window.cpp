#include "Window.h"

Window::Window() {
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	this->window = new sf::RenderWindow(sf::VideoMode(1920, 1080), "SFML works!", sf::Style::Default, settings);
}

Window& Window::getInstance(){
	static Window instance;
	return instance;
}