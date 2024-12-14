#pragma once
#include <vector>
#include "SFML/Graphics.hpp"

struct CollisionHelper
{
	std::vector<sf::RectangleShape>* p_spawn; 
	std::vector<sf::RectangleShape>* p_entitity;
	std::vector<sf::RectangleShape>* p_items;
};