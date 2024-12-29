#pragma once
#include "Common.h"


class Effects
{
public:
	enum Effect
	{
		Bloodscreen = 0,
	};

	void Initialize()
	{
		sf::Sprite sprite;
		auto toInsert = std::make_pair(Effect::Bloodscreen, sprite);
		m_effectsprites.insert(toInsert);
	}
	void Update()
	{
		m_hitscreentimer.CheckTimer(GameData::Player::_Enabled);
	}
	void Draw(sf::RenderWindow& window) const
	{
		if (!GameData::Player::_Enabled) { window.draw(m_effectsprites.find(Bloodscreen)->second); }
	}
	

private:
	void InitBloodScreen()
	{
		auto find = m_effectsprites.find(Effect::Bloodscreen);
		find->second.setTexture(Textures::_TextureHolder.Get(Textures::ID::BloodScreen));
		find->second.setColor(sf::Color(100, 0, 0, 150));
	}
	void InitDeathScreen()
	{
		// TODO: Hintergrund transparent-schwarz einfärben, score anzeigen, neustart oder exit anbieten.


	}

private:
	std::map<Effects::Effect, sf::Sprite> m_effectsprites;  
	Timer m_hitscreentimer; 
};