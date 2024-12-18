#pragma once
#include "SFML/Graphics.hpp"
#include "GameObject.h"

struct Bullet : public GameObject
{
	Bullet(const int &damage, const float &speed, Textures::ID id) : damage(damage), speed(speed), type(id) {}

	int damage;
	float speed;

	Textures::ID type; 

	sf::Vector2f direction;
	sf::Vector2f position;

	sf::RectangleShape body;
	sf::RectangleShape target;

	bool target_reached = false; 

	sf::FloatRect GetBoundingBox() const override
	{
		return body.getGlobalBounds();
	}

	void OnCollision(GameObject& other) override
	{
		switch (other.objectType)
		{
			// Skeleton == Player
		case Textures::ID::Player:
			break; 

		default: 
			target_reached = true;
			break; 
		}
	}
};

