#pragma once
#include "SFML/Graphics.hpp"
#include "ResourceHolder.h"
#include "Item.h"
#include "Player.h"

#include <iostream>
#include <vector>
#include <map>

//tmp
#include "ScoreBoard.h"

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

	Inventory()
	{}

	void Initialize(const TextureHolder& textures, const int& width, const int& height)
	{
		p_view = sf::View(sf::FloatRect(0, 0, width, height));

		for (int i = 0; i < m_slots; i++)
		{
			sf::RectangleShape* box = new sf::RectangleShape(); 
			m_storage.push_back(box);
		}

		m_backgroundcolor_slots = sf::Color(245,245,220,200);

		for (int i = 0; i < m_slots; i++) {
			m_storage[i]->setFillColor(sf::Color::Yellow);
			m_storage[i]->setOutlineColor(m_backgroundcolor_slots);
			m_storage[i]->setOutlineThickness(1);
			m_storage[i]->setSize(sf::Vector2f(m_slot_sizeX, m_slot_sizeY));
			m_storage[i]->setPosition(sf::Vector2f(width - m_slot_sizeX * (i + 1), height - m_slot_sizeY));
		}
		
		//AddItem(toTextureID(Wand)); 
		//AddItem(toTextureID(Sword));
	}
	void Update(const sf::Vector2f& mouseposition)
	{
		for (auto& box : m_storage)
		{
			if (box->getGlobalBounds().contains(mouseposition))
			{
				box->setFillColor(sf::Color::Yellow);
			}
			else
			{
				box->setFillColor(m_backgroundcolor_slots);
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
		for (const auto& box : m_storage) { window.draw(*box); }
		for (const auto& item : m_items)  { }
	}

	void AddItem(Textures::ID ID, const TextureHolder& textures) {

		Item* item; m_items.push_back(item);
		int currindex = m_items.size()-1; 

		// Nicht mehr Items als im inventar platz hat
		if (currindex <= m_slots) {

			sf::Vector2f calculatedposition;
			calculatedposition.x = m_storage[m_slots - 1 - currindex]->getPosition().x + 32; 
			calculatedposition.y = m_storage[m_slots - 1 - currindex]->getPosition().y + 32; 

			item->Initialize(textures, ID, calculatedposition); 
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
	int m_slots = 3; 
	int m_slot_sizeX = 128, m_slot_sizeY = 128;

	sf::Sprite m_background; 

	std::vector<Item*>				  m_items;
	std::vector<sf::RectangleShape*>  m_storage; 

	sf::Clock m_clock; 
	int		  m_itemDropPickTimer = 500; 

	sf::Color m_backgroundcolor_slots; 
};



