#pragma once
#include "SFML/Graphics.hpp"
#include "ResourceHolder.h"
#include <vector>
#include <map>



typedef ResourceHolder<sf::Texture, Textures::ID> TextureHolder;

class Inventory
{
public:

	enum Items
	{
		EMPTY,
		WAND,
		BOW,
		SWORD,
		POTION_HEALTH,
		POTION_STEALTH,
		POTION_DAMAGE
	};

	Inventory() : m_size(3)
	{}

	void Initialize(TextureHolder& textures, const int& width, const int& height)
	{
		this->p_view = sf::View(sf::FloatRect(0, 0, width, height));

		int boxWidth = 128, boxHeight = 128;

		for (int i = 0; i < m_size + 1; i++)
		{
			sf::RectangleShape box;
			box.setFillColor(sf::Color::White);
			box.setOutlineColor(sf::Color::Black);
			box.setOutlineThickness(1);
			box.setSize(sf::Vector2f(128, 128));
			box.setPosition(sf::Vector2f(width - boxWidth * i, height - boxHeight));
			m_storage.push_back(box);
		}
	}
	void Update(const sf::Vector2f& mouseposition)
	{
		for (auto& box : m_storage)
		{
			if (box.getGlobalBounds().contains(mouseposition))
			{
				box.setFillColor(sf::Color::Yellow);
			}
			else
			{
				box.setFillColor(sf::Color::White);
			}

		}
	}
	void Draw(sf::RenderWindow& window)
	{
		window.draw(m_background);
		for (const auto& box : m_storage) { window.draw(box); }
		for (const auto& item : m_items) { window.draw(item.second); }
	}

public:
	sf::View p_view; 
	 
private:

	int m_size; 

	sf::Sprite m_background; 

	std::map<Items, sf::Sprite> m_items; 
	std::vector<sf::RectangleShape> m_storage; 
};

