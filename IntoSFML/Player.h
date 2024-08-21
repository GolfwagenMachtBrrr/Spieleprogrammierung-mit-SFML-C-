#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "Bullet.h"
#include "TextureHolder.h"
#include <vector>

class Player
{
public: 
	Player() : m_speed(0.125/10), m_health(100) {}

	void Initalize(TextureHolder &textureholder); 
	void Update(const float &dt, sf::RenderWindow& window);
	void Draw(sf::RenderWindow& window); 

	sf::Vector2f GetPosition() const
	{
		return this->m_position; 
	}

	sf::FloatRect GetHitBox() const
	{
		return this->m_hitbox.getGlobalBounds();
	}

private: 
	void MovePlayer(const float& dt);

private: 

	sf::Texture		   m_texture; 
	sf::Sprite		   m_sprite; 

	sf::RectangleShape m_hitbox; 

	sf::Vector2f	   m_position;

	float			   m_speed; 
	int				   m_health; 

	// until its fixed
	int movementIndicator = 0; 
};

