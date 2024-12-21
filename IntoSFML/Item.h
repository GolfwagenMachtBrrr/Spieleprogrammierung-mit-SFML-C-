#pragma once
#include "SFML/Graphics.hpp"
#include "ResourceHolder.h"
#include "GameObject.h"

struct Item : public GameObject
{
	Item()
	{}
	
	void Initialize(const TextureHolder& textures,
					Textures::ID ID,
					const sf::Vector2f& position)
	{
		m_position = position; 
		m_sprite.setTexture(textures.Get(ID)); 

		objectType = ID;

		// ????
		m_sprite.setScale(sf::Vector2f(4, 4)); 
	}


};