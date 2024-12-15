#pragma once
#include "SFML/Graphics.hpp"
#include "ResourceHolder.h"
#include "GameObject.h"

#include <iostream>

class Entity : public GameObject
{
public: 
	Entity()
	{
	}

	Entity(const TextureHolder& textures, 
		   const Textures::ID ID,
		   const sf::Vector2f &size, 
		   const sf::Vector2f& position)
		: m_sprite(textures.Get(ID)), m_size(size), p_position(position)
	{
		this->p_hitbox.setPosition(position);
		this->p_hitbox.setSize(size);
		this->objectType = ID; 
	}

	void Update()
	{
		p_hitbox.setPosition(p_position);
		m_sprite.setPosition(p_position);
	}

	void Draw(sf::RenderWindow& window)
	{
		window.draw(m_sprite); 
	}

	sf::FloatRect GetBoundingBox() const override
	{
		return p_hitbox.getGlobalBounds(); 
	}

	void OnCollision(GameObject& other) override
	{
	}

public:

	sf::Vector2f	   p_position; 
	sf::RectangleShape p_hitbox; 

private: 
	sf::Sprite		m_sprite; 
	sf::Vector2f	m_size; 
};

