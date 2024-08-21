#pragma once
#include "SFML/Graphics.hpp"

struct Bullet
{
	Bullet(const int &damage, const float &speed) : damage(damage), speed(speed) {}

	int damage;
	float speed;

	sf::Vector2f direction;
	sf::Vector2f position;

	sf::RectangleShape body;
	sf::RectangleShape target;
};

