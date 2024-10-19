#pragma once
#include "SFML/Graphics.hpp"

#include "Entity.h"
#include "Item.h"
#include "ResourceHolder.h"
#include "Spawner.h"

#include <random>

class MapManager
{
public: 
	void Initialize(const TextureHolder& textures)
	{

	}
	void Update(); 
	void Draw(sf::RenderWindow& window)
	{
		for (auto& spawner : m_spawners) { spawner.Draw(window); }
		for (auto& entity  : m_entities) { entity.Draw(window);	 }
		// Item Draw
	}

	void AddSpawner(const int& amount); 
	void AddEntities(Textures::ID ID, const int& amount); 

private: 
	void InitSpawner(const TextureHolder& textures, const int& amount)
	{
		m_spawners = std::vector<Spawner>(amount);
		for (auto& spawner : m_spawners) {
			// Spawner Setup
		}
	}
	void InitHouses(const TextureHolder& textures, const int& amount)
	{
		int latestIndex = m_entities.size() - 1; 
		for (int index = latestIndex; index < latestIndex + amount; index++) {
			// Houses Setup
			Entity entity(textures,
						  Textures::ID::House, 
						  Textures::GetTextureSize(Textures::ID::House), 
						  CalculatePosition());

			m_entities.push_back(entity); 
		}
	}

	sf::Vector2f CalculatePosition()
	{
		// sollte sich nicht mit anderen instanzen von Entity überschneiden können
		int randX = rand() % 3000, randY = rand() % 3000;
		return sf::Vector2f(randX, randY); 
	}

private: 
	std::vector<Spawner> m_spawners; 
	std::vector<Entity>  m_entities; 
	std::vector<Item>	 m_items; 
};

