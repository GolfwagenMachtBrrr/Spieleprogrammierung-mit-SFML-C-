#pragma once
#include "nGameData.h"

struct Building : public GameObject
{

	Building(const Textures::ID tID, const Fonts::ID fID, const sf::Vector2f& InitialPosition) : GameObject(tID, fID, InitialPosition) {}

	void Draw(sf::RenderWindow& window) const noexcept override
	{
		if (GameData::Player::ValidateRendering(m_sprite)) { window.draw(m_sprite); }
	}

	void Update() override
	{

	}

	void OnCollision(GameObject& other) override {}
};