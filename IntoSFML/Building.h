#pragma once
#include "SFML/Graphics.hpp"

#include "GameObject.h"
#include "Player.h"


struct Building : public GameObject
{

	Building(const TextureHolder& textures,
		const Textures::ID ID,
		const sf::Vector2f& size,
		const sf::Vector2f& position)
	{
		m_sprite.setTexture(textures.Get(ID));
		m_sprite.setPosition(position);

		objectType = ID;
		m_position = position; 
	}

	void Draw(sf::RenderWindow& window, Player* player)
	{
		if (player->ValidateRendering(m_position)) {
			window.draw(m_sprite);
		}
	}

	// GameObject
	sf::FloatRect GetBoundingBox() const override
	{
		return m_sprite.getGlobalBounds();
	}

	sf::Vector2f GetPosition() const override
	{
		return m_position;
	}

	void OnCollision(GameObject& other) override
	{

	}
};