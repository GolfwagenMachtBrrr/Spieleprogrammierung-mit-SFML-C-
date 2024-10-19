#pragma once
#include "SFML/Graphics.hpp"
#include "ResourceHolder.h"

class Entity
{
public: 
	Entity()
	{
	}

	Entity(const TextureHolder& textures, Textures::ID ID, const sf::Vector2f &size, const sf::Vector2f& position)
		: m_sprite(textures.Get(ID)), m_size(size), p_position(position)
	{
		this->p_hitbox.setPosition(position); 
		this->p_hitbox.setSize(size);
	}

	void Draw(sf::RenderWindow& window)
	{
		window.draw(m_sprite); 
	}


public:

	sf::Vector2f	   p_position; 
	sf::RectangleShape p_hitbox; 

private: 
	sf::Sprite		m_sprite; 
	sf::Vector2f	m_size; 
};

