#pragma once

#include "global.hpp"
#include "Button.hpp"

class Screen
{
protected:
	sf::Vector2i mousePosition;
	Button back;
	sf::RenderWindow window;

public:
	void display();
};

