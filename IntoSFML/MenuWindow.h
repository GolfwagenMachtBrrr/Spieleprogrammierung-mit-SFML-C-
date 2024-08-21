#pragma once
#include "SFML/Window.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <SFML/Network.hpp>

#include"GameWindow.h"
#include "Settings.h"
#include <iostream>
#include <string>
#include <vector>

#define START 0
#define SETTINGS 1
#define CONFIG 2
#define EXIT 3


class MenuWindow
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
		m_menu_background.setPosition(sf::Vector2f(m_width / 4, 0));
		m_menu_background.setSize(sf::Vector2f(sf::Vector2f(m_width / 2, m_height)));
		m_menu_background.setFillColor(sf::Color(0, 0, 0, 150));

		this->m_texture_Background.loadFromFile("C:/Users/JanSa/OneDrive/Desktop/Programmieren/Projekte/ProcMapGen/ProcGen/Assets/AssetPack/Tiny Swords/Tiny Swords (Update 010)/UI/Buttons/Button_Disable_3Slides.png");
		this->m_texture_cursor.loadFromFile("C:/Users/JanSa/OneDrive/Desktop/Programmieren/Projekte/ProcMapGen/ProcGen/Assets/AssetPack/Tiny Swords/Tiny Swords (Update 010)/UI/Pointers/01.png");
		this->m_sprite_Background.setTexture(m_texture_Background);
		this->m_sprite_cursor.setTexture(m_texture_cursor);

		this->m_sprite_Background.setScale(sf::Vector2f(2, 1.5)); 
		this->m_menuTexts = std::vector<std::string>() = { "Start","Settings","Config","Exit" };
	

		for (int i = 0; i < m_menuTexts.size(); i++)
		{
			sf::Text text;
			text.setFont(m_menuFont);
			text.setFillColor(sf::Color::White);
			text.setString(m_menuTexts[i]);
			text.setCharacterSize(60);
			text.setPosition(sf::Vector2f(m_width - m_width / 2 - 60, ((i + 1) * 200)));
			m_menuItems.push_back(text);
		}

	}
	void InitWindow()
	{
		this->m_window.create(sf::VideoMode(m_width, m_height), "GameMenu");
		this->m_window.setMouseCursorVisible(false); 
	}
	void Update()
	{
		m_sprite_cursor.setPosition(static_cast<sf::Vector2f>(sf::Mouse::getPosition(m_window)));

		for (int i = 0; i < m_menuItems.size(); i++)
		{
			if (m_menuItems[i].getGlobalBounds().contains(m_sprite_cursor.getPosition().x, m_sprite_cursor.getPosition().y))
			{
				m_menuItems[i].setFillColor(sf::Color::Yellow);
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					switch (i)
					{
					case START:
						m_game.Start(true); 
						break;

					case EXIT:
						m_window.close();
						break;
					}
				}
			}
			else
			{
				m_menuItems[i].setFillColor(sf::Color::White);
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
			m_window.draw(m_menu_background); 
			for (auto& i : m_menuItems)
			{
				m_sprite_Background.setPosition(sf::Vector2f(i.getPosition().x - 60, i.getPosition().y));
				m_window.draw(m_sprite_Background);
				m_window.draw(i);
			}

			m_window.draw(m_sprite_cursor);
			m_window.display();
		}
	}

private:
	int						  m_width = 1920; 
	int						  m_height = 1080; 
							 
	sf::RenderWindow		  m_window;
	sf::Font				  m_menuFont;
							 
	sf::Texture				  m_texture_Background, m_texture_cursor; 
	sf::Sprite				  m_sprite_Background, m_sprite_cursor;
	sf::RectangleShape		  m_menu_background; 
							 
							 
	std::vector<sf::Text>	  m_menuItems;
	std::vector<std::string>  m_menuTexts;
							 
	Settings				  m_settings;
	GameWindow				  m_game;
};

