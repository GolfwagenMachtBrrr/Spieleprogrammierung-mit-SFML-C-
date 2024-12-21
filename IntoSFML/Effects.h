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
		m_bloodscreen.setColor(sf::Color(100, 0, 0, 150)); 
		m_bloodscreen.setPosition(0, 0); 
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


	int m_duration = 2500; 
	bool playerhit = false;  
};