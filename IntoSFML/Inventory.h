#pragma once
#include "SFML/Graphics.hpp"
#include "ResourceHolder.h"
#include <vector>
#include <map>

#include <iostream>



typedef ResourceHolder<sf::Texture, Textures::ID> TextureHolder;

class Inventory
{
public:

	enum Items
	{
		Wand,
		Sword,
		Shield,
	};

	Inventory() : m_size(3)
	{}

	void Initialize(const TextureHolder& textures, const int& width, const int& height)
	{
		this->p_view = sf::View(sf::FloatRect(0, 0, width, height));
		std::cout << m_size << " Size " << std::endl; 

		int boxWidth = 128, boxHeight = 128;

		for (int i = 0; i < m_size; i++)
		{
			sf::RectangleShape box; m_storage.push_back(box);
		}

		for (int i = 0; i < m_size; i++) {
			m_storage[i].setFillColor(sf::Color::Transparent);
			m_storage[i].setOutlineColor(sf::Color::Black);
			m_storage[i].setOutlineThickness(1);
			m_storage[i].setSize(sf::Vector2f(boxWidth, boxHeight));
			m_storage[i].setPosition(sf::Vector2f(width - boxWidth * (i + 1), height - boxHeight));
		}
		

		AddGlobalItem(toTextureID(Wand), textures);
		AddGlobalItem(toTextureID(Sword), textures);

		AddItem(toTextureID(Wand)); 
		AddItem(toTextureID(Sword));
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
				box.setFillColor(sf::Color::Transparent);
			}

		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::F)) {
			if (m_items.size() != 0 && TimePassed()) {
				m_items.pop_back();
			}
			
		}
	}
	void Draw(sf::RenderWindow& window)
	{
		window.draw(m_background);
		for (const auto& box : m_storage) { window.draw(box); }
		for (const auto& item : m_items) { window.draw(item); }
	}

	void AddItem(Textures::ID id) {
		auto found = m_itemlist.find(id);
		m_items.push_back(found->second); 
		
		int currindex = m_items.size()-1; 

		if (currindex <= m_size) {
			m_items[currindex].setPosition(sf::Vector2f
			(m_storage[m_size-1  - currindex].getPosition().x + 32, m_storage[m_size - 1 - currindex].getPosition().y + 32));
			m_items[currindex].scale(sf::Vector2f(4, 4)); 
		}
		else {
			std::cout << "Inventory Full - Drop an Item to make space in your Inventory"; 
		}
	}
	
private: 
	// Ausm Buch
	Textures::ID toTextureID(Inventory::Items item) {
		switch (item)
		{
		case Items::Sword:
			return Textures::ID::Sword; 
		case Items::Wand:
			return Textures::ID::Wand; 
		}
	}

	void AddGlobalItem(Textures::ID id, const TextureHolder &textures)
	{
		sf::Sprite item(textures.Get(id));
		m_itemlist.insert(std::make_pair(id, item)); 
	}

	bool TimePassed()
	{
		int timepassed = m_clock.getElapsedTime().asMilliseconds();
		if (timepassed >= m_itemDropPickTimer) {
			m_clock.restart(); 
			return true; 
		}
		return false;
	}

public:
	sf::View p_view; 
	 
private:

	int m_size; 

	sf::Sprite m_background; 

	std::vector<sf::Sprite>				  m_items;
	std::map<Textures::ID, sf::Sprite>	  m_itemlist;
	std::vector<sf::RectangleShape>       m_storage; 

	sf::Clock m_clock; 
	int		  m_itemDropPickTimer = 500; 
};

