#pragma once
#include "SFML/Graphics.hpp"

#include "Entity.h"
#include "Item.h"
#include "ResourceHolder.h"
#include "Spawner.h"
#include "Player.h"
#include "MapGenerator.h"

#include <random>
#include <vector>


class MapManager
{
public: 
	void Initialize(const TextureHolder& textures, MapGenerator& map)
	{
		InitHouses(textures, 20, map); 
		InitSpawner(textures, 1, 1, map); 
	}
	void Update(const float &deltatime, Player &player, MapGenerator &map)
	{
		for (auto& entity : m_entities) { entity.Update();}
		for (auto& spawner : m_spawners) { spawner.Update(deltatime, player, map); }
	}
	void Draw(sf::RenderWindow& window)
	{ 
		for(auto& spawner : m_spawners) { spawner.Draw(window); }
		for (auto& entity  :  m_entities) { entity.Draw(window);	}
		// Item Draw
	}

	void AddSpawner(const int& amount); 
	void AddEntities(Textures::ID ID, const int& amount); 

private: 
	void InitSpawner(const TextureHolder& textures, const int& amount, const int& density, MapGenerator &map)
	{
		for (int i = 0; i < amount; i++) { Spawner spawner; m_spawners.push_back(spawner); }
		for (auto& spawner : m_spawners) {
			std::vector<Textures::ID> spawntypes; 
			for (int i = 0; i < density; i++) { spawntypes.push_back(Textures::ID::Zombie); }
			std::cout << "Iam here" << std::endl; 
			spawner.Initialize(CalculatePosition(map, Textures::ID::Spawner), spawntypes, textures);

		}
	}
	void InitHouses(const TextureHolder& textures, const int& amount, MapGenerator &map)
	{
		int latestIndex = m_entities.size() - 1; 
		for (int i = 0; i < amount; i++) {
			// Houses Setup
			sf::Vector2f newposition = CalculatePosition(map, Textures::ID::House);
			Entity entity(textures,
						  Textures::ID::House, 
						  GetTextureSize(Textures::ID::House), 
						  newposition);

			m_entities.push_back(entity); 
		}
	}

	sf::Vector2f CalculatePosition(MapGenerator& map, Textures::ID ID)
	{
		sf::Vector2f calculatedposition; 

		calculatedposition.x = rand() % 1500 + 200;
		calculatedposition.y = rand() % 1500 + 200;

		AdjustTileMap(map, calculatedposition, ID);
		
		return calculatedposition;
	}

	void AdjustTileMap(MapGenerator& map, const sf::Vector2f &calculatedposition, Textures::ID ID)
	{
		sf::Vector2f tilesize = static_cast<sf::Vector2f>(map.GetTileSize());
		int startX = calculatedposition.x / tilesize.x, endX = GetTextureSize(ID).x / tilesize.x;
		int startY = calculatedposition.y / tilesize.y, endY = GetTextureSize(ID).y / tilesize.y;

		for (int i = startX; i < startX + endX; i++) {
			for (int j = startY; j < startY + endY; j++)
			{
				map.p_tileMap[i][j].occupied = true; 
				map.p_tileMap[i][j].occupationID = ID; 
			}
		}
	}

	bool EntityIsOverlapping(const sf::Vector2f &position)
	{
		sf::RectangleShape hypotheticalHitbox; hypotheticalHitbox.setPosition(position); 
		for (int i = 0; i < m_entities.size() - 1; i++) {
			if (CollisionCheck(hypotheticalHitbox.getGlobalBounds(),
				m_entities[i].p_hitbox.getGlobalBounds()))
			{
				return true; 
			}
		}
		return false; 
	}

	bool CollisionCheck(const sf::FloatRect& a, const sf::FloatRect& b)
	{
		if (a.left + a.width > b.left &&
			b.left + b.width > a.left &&
			b.top + b.height > a.top &&
			a.top + a.height > b.top)
		{
			return true;
		}
		return false;
	}

	const sf::Vector2f GetTextureSize(Textures::ID ID)
	{
		switch (ID) {

		case Textures::ID::House:
			return sf::Vector2f(128, 192);
		case Textures::ID::Spawner:
			return sf::Vector2f(100, 80); 
		}
	}

	bool TimePassed()
	{
		int timepassed = m_clock.getElapsedTime().asMilliseconds();
		if (timepassed >= m_timer) {
			m_clock.restart();
			return true;
		}
		return false;
	}

private: 
	std::vector<Spawner> m_spawners; 
	std::vector<Spawner> notavectorofspawners;
	std::vector<Entity>  m_entities; 
	std::vector<Item>	 m_items; 

	sf::Clock m_clock; 
	int m_timer = 500;

};

