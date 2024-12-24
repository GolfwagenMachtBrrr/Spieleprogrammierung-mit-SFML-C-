#pragma once
#include "SFML/Graphics.hpp"
#include "GameObject.h"
#include "Entity.h"

struct Bullet : public GameObject, public Entity 
{
	Bullet(const TextureHolder& textures, Textures::ID ID, const sf::Vector2f& position, float rotation) 
	{
		// Entity & Gameobject values set
		Entity::m_damage = 10; 
		Entity::m_speed = 0.125; 

		GameObject::m_position = position;
		GameObject::objectType = ID; 
	
		GameObject::m_sprite.setTexture(textures.Get(ID));
		GameObject::m_sprite.setPosition(position);

		GameObject::m_sprite.setOrigin(GameObject::m_sprite.getLocalBounds().width / 2, 0);
		GameObject::m_sprite.setRotation(-90);
		GameObject::m_sprite.rotate(rotation);

	}

	sf::RectangleShape target;
	bool			   target_reached = false; 

	void OnCollision(GameObject& other) override
	{
		switch (other.objectType)
		{
		case Textures::ID::Player:
			break; 

		default: 
			target_reached = true;
			break; 
		}
	}
};

