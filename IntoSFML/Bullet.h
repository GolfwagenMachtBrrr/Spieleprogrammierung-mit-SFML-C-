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

	sf::RectangleShape body;
	sf::RectangleShape target;

	bool target_reached = false; 

	// GameObject

	sf::Vector2f GetPosition() const override
	{
		return m_position; 
	}

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


private: 
	sf::Vector2f m_position;

};

