#pragma once
#pragma once
#include "SFML/Graphics.hpp"

struct WayPoint
{
	sf::Vector2f position;
	sf::Vector2f target;

	bool isActive;
};