#pragma once
#include "SFML/Graphics.hpp"

#include "Inventory.h"
#include "ScoreBoard.h"
#include "Effects.h"

#include "ResourceHolder.h"
#include "Player.h"


// TODO

class HUD
{
public:
	void Initalize(const TextureHolder &textures, int window_width, int window_height)
	{
		m_inventory.Initialize(textures, window_width, window_height); 
		m_scoreboard.Initialize();
		m_effects.Initialize(textures);
	}

	void Update(const sf::Vector2f& adjustedmouseposition, Player* player)
	{
		m_inventory.Update(adjustedmouseposition);
		m_scoreboard.Update(player);
		m_effects.Update(player); 
	}

	void Draw(sf::RenderWindow& window)
	{
		m_inventory.Draw(window); 
		m_scoreboard.Draw(window);
		m_effects.Draw(window); 
	}

private: 
	Inventory  m_inventory; 
	ScoreBoard m_scoreboard; 
	Effects	   m_effects; 
};

