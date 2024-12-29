#pragma once
#include "Common.h"
#include "nRessources.h"
#include "nGameData.h"

class Inventory  
{
public:
	Inventory()
	{
		std::cout << "STD" << std::endl;
	}

	void Initialize(const int& width, const int& height)
	{
		for (int i = 0; i < m_slots; i++)
		{
			sf::RectangleShape* box = new sf::RectangleShape();
			m_storage.push_back(box);
		}

		m_backgroundcolor_slots = sf::Color(245, 245, 220, 200);

		for (int i = 0; i < m_slots; i++) {
			m_storage[i]->setFillColor(sf::Color::Yellow);
			m_storage[i]->setOutlineColor(m_backgroundcolor_slots);
			m_storage[i]->setOutlineThickness(1);
			m_storage[i]->setSize(sf::Vector2f(m_slot_sizeX, m_slot_sizeY));
			m_storage[i]->setOrigin(m_storage[i]->getLocalBounds().width / 2, m_storage[i]->getLocalBounds().height / 2);
			m_storage[i]->setPosition(sf::Vector2f(width - m_slot_sizeX * (i + 1) + m_slot_sizeX / 2, height - m_slot_sizeY / 2));
		}

		AddItem(Textures::ID::Wand, Fonts::OnlyFont);
	}
	void Update()
	{
		for (auto& box : m_storage)
		{
			if (box->getGlobalBounds().contains(GameData::Views::_HUDMousePosition))
			{
				box->setFillColor(sf::Color::Yellow);
			}
			else
			{
				box->setFillColor(m_backgroundcolor_slots);
			}

		}
		for (auto& item : m_items) { item->Update(); }
	}
	void Draw(sf::RenderWindow& window)
	{
		window.draw(m_background);
		for (const auto& box : m_storage) { window.draw(*box); }
		for (const auto& item : m_items) { item->Draw(window); }
	}
	void AddItem(Textures::ID tID, Fonts::ID fID)
	{
		int currindex = m_items.size();
		if (currindex > m_slots) { return; }

		sf::Vector2f calculatedposition;
		calculatedposition.x = m_storage[m_slots - currindex - 1]->getPosition().x;
		calculatedposition.y = m_storage[m_slots - currindex - 1]->getPosition().y;

		Item* item = new Item(tID, fID, calculatedposition);
		m_items.push_back(item);



	}
	 
private:
	int m_slots = 3; 
	int m_slot_sizeX = 128, m_slot_sizeY = 128;

	sf::Sprite m_background; 
	sf::Color  m_backgroundcolor_slots;

	std::vector<Item*>				  m_items;
	std::vector<sf::RectangleShape*>  m_storage; 
};



