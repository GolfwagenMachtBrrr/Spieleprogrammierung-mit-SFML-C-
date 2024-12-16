#pragma once
#include "SFML/Graphics.hpp"
#include "ResourceHolder.h"


class GameObject
{
public: 
	int objectID = -1;
	Textures::ID objectType = Textures::ID::Undefined; 
	bool active = true; 

	virtual sf::FloatRect GetBoundingBox() const = 0;
	virtual void OnCollision(GameObject &other) = 0; 

private: 
	sf::Vector2f m_position; 
};