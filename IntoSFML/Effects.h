#pragma once
#include "Common.h"
#include <string>
#include "nRessources.h"


class Effects
{
public:

	void Initialize()
	{
		AddEffect(Textures::ID::BloodScreen);
		AddEffect(Textures::ID::DeathScreen);


		SetupTextures(); 
		InitDeathScreen(); 
	}
	void Update()
	{
		for (int i = 0; i < m_optionboxes.size(); i++)
		{
			if (m_optionboxes[i].first->getGlobalBounds().contains(GameData::Views::_HUDMousePosition))
			{
				m_optionboxes[i].first->setFillColor(sf::Color::Yellow);
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{

				}
			}
			else
			{
				m_optionboxes[i].first->setFillColor(sf::Color(255, 255, 255, 150));
			}
		}
	}
	void Draw(sf::RenderWindow& window)
	{
		if (GameData::Player::_PlayerHealth <= 0) { 
			if (!DeathSoundHasBeenPlayer) {
				m_playerdeath.play(); 
				DeathSoundHasBeenPlayer = true; 
			}
			window.draw(m_effectsprites.find(Textures::ID::DeathScreen)->second); 
			for (const auto& textbox : m_optionboxes)
			{
				window.draw(*textbox.first); 
				window.draw(*textbox.second); 
			}

			return; 
		}

		if (!GameData::Player::_Enabled) { window.draw(m_effectsprites.find(Textures::ID::BloodScreen)->second); }
		

	}
	

private:
	void AddEffect(Textures::ID ID)
	{
		sf::Sprite sprite;
		auto toInsert = std::make_pair(ID, sprite);
		m_effectsprites.insert(toInsert);
	}

	void SetupTextures()
	{
		auto find = m_effectsprites.find(Textures::ID::BloodScreen);
		find->second.setTexture(Textures::_TextureHolder.Get(Textures::ID::BloodScreen));
		find->second.setColor(sf::Color(100, 0, 0, 150));

		find = m_effectsprites.find(Textures::ID::DeathScreen);
		find->second.setTexture(Textures::_TextureHolder.Get(Textures::ID::DeathScreen));

		m_playerdeath.setBuffer(Sounds::_SoundHolder.Get(Sounds::ID::SoundPlayerDeath)); 
	}
	void InitDeathScreen()
	{
		// TODO: Hintergrund transparent-schwarz einfärben, score anzeigen, neustart oder exit anbieten.
		for (int i = 0; i < m_options; i++)
		{
			sf::RectangleShape* box = new sf::RectangleShape(); 
			box->setFillColor(sf::Color(255,255,255,150)); 
			box->setPosition(GameData::_WindowSize.x / 2 - i*128, GameData::_WindowSize.y / 2);
			box->setSize(sf::Vector2f(128,32)); 

			sf::Text* text = new sf::Text(); 
			text->setFont(Fonts::_FontHolder.Get(Fonts::ID::OnlyFont)); 
			text->setCharacterSize(24); 
			text->setPosition(box->getPosition());
			text->setString(m_texts[i]); 

			auto optionbox = std::make_pair(box, text); 
			m_optionboxes.push_back(optionbox); 
		}

	}


private:
	std::map<Textures::ID, sf::Sprite> m_effectsprites;  
	Timer m_hitscreentimer; 

	bool DeathSoundHasBeenPlayer = false;
	sf::Sound m_playerdeath; 

	std::vector<std::pair<sf::RectangleShape*, sf::Text*>> m_optionboxes; 
	std::vector<std::string> m_texts = {"Restart", "Exit"};
	int m_options = 2;
};