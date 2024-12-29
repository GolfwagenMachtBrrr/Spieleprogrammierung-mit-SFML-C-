#include "Common.h"
#include "nGameData.h"

class ScoreBoard
{
public:
	void Initialize()
	{
		m_texts = std::vector<sf::Text>(2);
		m_texts[0].setFont(Fonts::_FontHolder.Get(Fonts::ID::OnlyFont));
		m_texts[0].setCharacterSize(24);
		m_texts[0].setPosition(sf::Vector2f(1920 - 128 * 2, 0));

		m_texts[1].setFont(Fonts::_FontHolder.Get(Fonts::ID::OnlyFont));
		m_texts[1].setCharacterSize(24);
		m_texts[1].setPosition(sf::Vector2f(1920 - 128 * 2, 128 / 4));


		m_displaybox.setSize(sf::Vector2f(128 * 2, 128));
		m_displaybox.setPosition(sf::Vector2f(1920 - 128 * 2, 0));
		m_displaybox.setFillColor(sf::Color(100, 100, 100, 150));
	}
	void Update()
	{
		m_texts[0].setString("Current Kills: " + std::to_string(GameData::Player::_TotalEnemiesKilled));
		m_texts[1].setString("Current Health: Hier wird etwas sinvolles stehen");
	}
	void Draw(sf::RenderWindow& window)
	{
		for (auto& text : m_texts) { window.draw(text); }
		window.draw(m_displaybox);
	}

private:
	std::vector<sf::Text>  m_texts; 
	sf::RectangleShape     m_displaybox;

};