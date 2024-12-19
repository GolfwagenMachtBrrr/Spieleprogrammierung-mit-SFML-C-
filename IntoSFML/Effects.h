#pragma once
#include "SFML/Graphics.hpp"
#include "ResourceHolder.h"
#include "Player.h"


class Effects
{
public:
	void Initialize(const TextureHolder& textures)
	{
		m_bloodscreen.setTexture(textures.Get(Textures::ID::BloodScreen));
	}
	void Update(Player* player)
	{
		DamnThatBloodyDuration(player); 
		playerhit = player->p_onhit; 
	}
	void Draw(sf::RenderWindow& window) const
	{
		if (playerhit) {
			window.draw(m_bloodscreen); 
		}
	}

private: 
	bool DamnThatBloodyDuration(Player* player)
	{
		if (this->m_thatbigclock.getElapsedTime().asMilliseconds() >= this->m_duration)
		{
			this->m_thatbigclock.restart();
			player->p_onhit = false; 
			return true;
		}
		return false;
	}

private:
	sf::Sprite m_bloodscreen; 
	sf::Clock  m_thatbigclock; 


	int m_duration = 2000; 
	bool playerhit = false;  
};