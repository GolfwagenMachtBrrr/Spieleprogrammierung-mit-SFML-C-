#pragma once
#include "SFML/Graphics.hpp"


class ScoreBoard
{
public:
	void Initialize()
	{
		m_font.loadFromFile("C:/Users/JanSa/OneDrive/Desktop/Programmieren/Projekte/ProcMapGen/ProcGen/Assets/Fonts/NotoSansThai-Regular.ttf");
		m_text.setFont(m_font); 
		m_text.setCharacterSize(24); 
		m_text.setPosition(sf::Vector2f(1920 - 128 * 2, 0));

		m_text.setString("Hier wird text angezeigt");

		m_displaybox.setSize(sf::Vector2f(128 * 2, 128));
		m_displaybox.setPosition(sf::Vector2f(1920 - 128 * 2, 0));
		m_displaybox.setFillColor(sf::Color(100, 100, 100, 150));



	}
	void Update(Player* player);
	void Draw(sf::RenderWindow& window)
	{
		window.draw(m_text); 
		window.draw(m_displaybox);
	}

private:
	sf::Font m_font; 
	sf::Text m_text;
	sf::RectangleShape m_displaybox;

};