#pragma once
#include "SFML/Graphics.hpp"
#include "TextureHolder.h"
#include <vector>
#include <map>


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

	Inventory() : m_size(3) {}

	void Initialize(TextureHolder &textures, const int& width, const int& height);
	void Update(const sf::Vector2f& mouseposition);
	void Draw(sf::RenderWindow& window);

public:
	sf::View p_view; 
	 
private:

	int m_size; 

	sf::Texture m_background_texture; 
	sf::Sprite m_background; 

	std::map<Items, sf::Sprite> m_items; 
	std::vector<sf::RectangleShape> m_storage; 
};

