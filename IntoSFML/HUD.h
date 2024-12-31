#pragma once 
#include "Common.h"

#include "Inventory.h"
#include "ScoreBoard.h"
#include "Effects.h"


#include "nRessources.h"
#include "nGameData.h"

class HUD
{
public:
	void Initalize(int window_width, int window_height)
	{
		HUDView = sf::View(sf::FloatRect(0, 0, window_width, window_height));
		m_inventory.Initialize(window_width, window_height);
		m_scoreboard.Initialize();
		m_effects.Initialize();

		this->m_cursor.setTexture(Textures::_TextureHolder.Get(Textures::ID::Cursor));
	}
	void Update()
	{
		m_inventory.Update();
		m_scoreboard.Update();
		m_effects.Update();

		m_cursor.setPosition(GameData::Views::_HUDMousePosition);
	}
	void Draw(sf::RenderWindow& window)
	{
		window.setView(HUDView);

		m_inventory.Draw(window);
		m_scoreboard.Draw(window);
		m_effects.Draw(window);

		window.draw(m_cursor);
	}

private:
	Inventory  m_inventory; 
	ScoreBoard m_scoreboard; 
	Effects	   m_effects; 
	
	sf::Sprite m_cursor; 

	sf::View HUDView; 
};

