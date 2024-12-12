#pragma once
#include "SFML/Graphics.hpp"

class GameObject
{
public: 
	int objectID = -1;
	virtual sf::FloatRect GetBoundingBox() const = 0;
	virtual void OnCollision(GameObject &other) = 0; 
};