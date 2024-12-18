#pragma once
#include "SFML/Graphics.hpp"
#include "ResourceHolder.h"

// enabled sollte verwendet werden um zu überprüfen
// ob z.b ein zombie bereits wieder angreifen kann. 
// Sollte dann in enemy->Update() aktualisiert werden. 

class GameObject
{
public: 
	int objectID = -1;
	Textures::ID objectType = Textures::ID::Undefined;

	bool active = true; 
	bool enabled = true; 

	virtual sf::FloatRect GetBoundingBox() const = 0;
	virtual void OnCollision(GameObject &other) = 0; 

private: 
	sf::Vector2f m_position; 
};