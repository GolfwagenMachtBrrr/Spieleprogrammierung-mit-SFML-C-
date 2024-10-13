#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "Bullet.h"
#include "TextureHolder.h"
#include <vector>

class Player
{
public: 
	Player() : m_speed(0.125/10), p_health(100) {}

	void Initalize(TextureHolder &textureholder); 
	void Update(const float &dt, sf::RenderWindow& window);
	void Draw(sf::RenderWindow& window); 

	sf::Vector2f GetPosition()
	{
		return this->m_position; 
	}


private: 
	void MovePlayer(const float& dt);

public: 
	sf::RectangleShape p_hitbox;
	int				   p_health;
private: 

	sf::Texture		   m_texture; 
	sf::Sprite		   m_sprite; 

	sf::Vector2f	   m_position;
	float			   m_speed; 

	// until its fixed
	int movementIndicator = 0; 
};

