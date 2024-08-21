#include "Inventory.h"
#include <iostream>

void Inventory::Initialize(TextureHolder& textures, const int &width, const int& height)
{
	this->p_view = sf::View(sf::FloatRect(0, 0, width, height)); 

	std::cout << width << " " << height << std::endl; 

	int boxWidth = 128, boxHeight = 128; 

	for (int i = 0; i < m_size+1; i++)
	{
		sf::RectangleShape box; 
		box.setFillColor(sf::Color::White);
		box.setOutlineColor(sf::Color::Black); 
		box.setOutlineThickness(1);
		box.setSize(sf::Vector2f(128, 128)); 
		box.setPosition(sf::Vector2f(width-boxWidth*i, height - boxHeight));
		m_storage.push_back(box); 
	}
}

void Inventory::Update(const sf::Vector2f &mouseposition)
{
	for (auto& box : m_storage)
	{
		if (box.getGlobalBounds().contains(mouseposition))
		{
			box.setFillColor(sf::Color::Yellow);
		}
		//box.setFillColor(sf::Color::White);
	}
}

void Inventory::Draw(sf::RenderWindow &window)
{
	window.draw(m_background); 
	for (const auto& box : m_storage) { window.draw(box); }
	for (const auto& item : m_items) { window.draw(item.second); }
}
