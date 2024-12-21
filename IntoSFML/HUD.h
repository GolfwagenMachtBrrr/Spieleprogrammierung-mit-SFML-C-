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
		p_inventory.Initialize(textures, window_width, window_height); 
		p_scoreboard.Initialize();
		p_effects.Initialize(textures);

		this->m_cursor.setTexture(textures.Get(Textures::ID::Cursor));
	}

	void Update(const sf::Vector2f& adjustedmouseposition, Player* player)
	{
		p_inventory.Update(adjustedmouseposition);
		p_scoreboard.Update(player);
		p_effects.Update(player); 

		m_cursor.setPosition(adjustedmouseposition);
	}

	void Draw(sf::RenderWindow& window)
	{
		window.setView(p_inventory.p_view);

		p_inventory.Draw(window); 
		p_scoreboard.Draw(window);
		p_effects.Draw(window); 

		window.draw(m_cursor); 
	}

	Inventory  p_inventory; 
	ScoreBoard p_scoreboard; 
	Effects	   p_effects; 
	
private: 
	sf::Sprite m_cursor; 
};

