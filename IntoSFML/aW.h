#pragma once
#include "SFML/Window.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <SFML/Network.hpp>

#include "Game.h"
#include "Settings.h"
#include <iostream>
#include <string>
#include <vector>

#define START 0
#define SETTINGS 1
#define CONFIG 2
#define EXIT 3

class Menu
{
public:

	void start()
	{
		this->InitFont();
		this->InitWindow();
		this->InitTextures();
		this->MenuLoop();
	}

	void InitFont()
	{
		this->m_menuFont.loadFromFile("C:/Users/JanSa/OneDrive/Desktop/Programmieren/Projekte/ProcMapGen/ProcGen/Assets/Fonts/NotoSansThai-Regular.ttf");
	}
	void InitTextures() // Schreib endlich den verdammten TextureHolder du fauler Sack! 
	{
		sf::Texture textBackground, cursor;
		sf::Sprite sprite_tb, sprite_c;

		textBackground.loadFromFile("C:/Users/JanSa/OneDrive/Desktop/Programmieren/Projekte/ProcMapGen/ProcGen/Assets/AssetPack/Tiny Swords/Tiny Swords (Update 010)/UI/Buttons/Button_Disable_3Slides.png");
		cursor.loadFromFile("C:/Users/JanSa/OneDrive/Desktop/Programmieren/Projekte/ProcMapGen/ProcGen/Assets/AssetPack/Tiny Swords/Tiny Swords (Update 010)/UI/Pointers/01.png");
		sprite_tb.setTexture(textBackground);
		sprite_c.setTexture(cursor);

		this->m_sprites.push_back(sprite_tb);
		this->m_sprites.push_back(sprite_c);
		this->m_textures.push_back(textBackground);
		this->m_textures.push_back(cursor);
	}
	void InitWindow()
	{
		this->m_window.create(sf::VideoMode(1920, 1080), "GameMenu");
	}
	void Update()
	{
		m_sprites[1].setPosition(static_cast<sf::Vector2f>(sf::Mouse::getPosition(m_window)));

		for (int i = 0; i < m_menuItems.size(); i++)
		{
			if (m_menuItems[i].getGlobalBounds().contains(m_sprites[1].getPosition().x, m_sprites[1].getPosition().y))
			{
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					switch (i)
					{
					case START:
						std::cout << "Start Game" << std::endl;
						break;

					case EXIT:
						m_window.close();
						break;
					}
				}
			}
		}
	}
	void MenuLoop()
	{
		while (m_window.isOpen())
		{
			sf::Event event;
			while (m_window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
				{
					m_window.close();
				}

			}

			m_window.clear(sf::Color::White);
			this->Update();
			for (auto& i : m_menuItems)
			{
				m_sprites[0].setPosition(sf::Vector2f(i.getPosition().x - 60, i.getPosition().y));
				m_window.draw(m_sprites[0]);
				m_window.draw(i);
			}

			m_window.draw(m_sprites[1]);
			m_window.display();
		}
	}

private:

	sf::RenderWindow		 m_window;
	sf::Font				 m_menuFont;

	std::vector<sf::Sprite>  m_sprites;
	std::vector<sf::Texture> m_textures;
	std::vector<sf::Text>	 m_menuItems;
	std::vector<std::string> m_menueTexts;

	Settings				 m_settings;
	Game					 m_game;
};

