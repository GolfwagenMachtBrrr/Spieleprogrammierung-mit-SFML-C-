#pragma once
#include "SFML/Graphics.hpp"
#include "ResourceHolder.h"

// enabled sollte verwendet werden um zu überprüfen
// ob z.b ein zombie bereits wieder angreifen kann. 
// Sollte dann in enemy->Update() aktualisiert werden. 

class GameObject
{
public:
	virtual void OnCollision(GameObject& other) = 0;
	virtual sf::FloatRect GetBoundingBox() const = 0;

	virtual sf::Vector2f GetPosition() const = 0;

protected:
	void HandleCollision(const sf::Vector2f objectposition, float force) {
		sf::Vector2f direction = m_position - objectposition;
		float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
		if (length > 0) {
			direction /= length; 
			m_position += direction * force;
		}
	}

protected:
	sf::Vector2f     m_position;
	sf::Sprite		 m_sprite;

public:
	Textures::ID objectType = Textures::ID::Undefined;
	// Utility

	bool u_active = true;
	bool u_enabled = true;
	int  u_objectID = -1;
};