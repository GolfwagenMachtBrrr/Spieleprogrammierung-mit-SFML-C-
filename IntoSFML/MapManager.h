#pragma once
#include "SFML/Graphics.hpp"

#include "Entity.h"
#include "Item.h"
#include "ResourceHolder.h"
#include "Spawner.h"
#include "Player.h"
#include "MapGenerator.h"
#include "CollisionManager.h"

#include <random>
#include <vector>


class MapManager
{
public: 
	void Initialize(const TextureHolder& textures, MapGenerator& map, CollisionManager &collisionmanager)
	{
		InitHouses(textures, 1, map, collisionmanager); 
		InitSpawner(textures, 1, 2, map, collisionmanager);

	}
	void Update(const float &deltatime, Player &player, MapGenerator &map)
	{
		for (auto& entity : p_entities) { entity->Update();}
		for (auto& spawner :p_spawners) { spawner->Update(deltatime, player, map); }
	}
	void Draw(sf::RenderWindow& window)
	{ 
		for(auto& spawner : p_spawners) { spawner->Draw(window); }
		for (auto& entity  : p_entities) { entity->Draw(window);	}
		// Item Draw
	}

	void AddSpawner(const int& amount); 
	void AddEntities(Textures::ID ID, const int& amount); 

private: 
	void InitSpawner(const TextureHolder& textures, const int& amount, const int& density, MapGenerator &map, CollisionManager& collisionmanager)
	{
		for (int i = 0; i < amount; i++) { Spawner* spawner = new Spawner(); p_spawners.push_back(spawner); }
		for (auto& spawner : p_spawners) {
			std::vector<Textures::ID> spawntypes; 
			for (int i = 0; i < density; i++) { spawntypes.push_back(Textures::ID::Zombie); }
			spawner->Initialize(CalculatePosition(map, Textures::ID::Spawner), spawntypes, textures, collisionmanager);
		}
	}
	void InitHouses(const TextureHolder& textures, const int& amount, MapGenerator &map, CollisionManager& collisionmanager)
	{
		int latestIndex = p_entities.size() - 1; 
		for (int i = 0; i < amount; i++) {
			// Houses Setup
			sf::Vector2f newposition = CalculatePosition(map, Textures::ID::House);
			Entity* entity = new Entity(textures,
										Textures::ID::House, 
										GetTextureSize(Textures::ID::House), 
										newposition);
			collisionmanager.addObject(entity);
			p_entities.push_back(entity); 
		}
	}

	sf::Vector2f CalculatePosition(MapGenerator& map, Textures::ID ID)
	{
		sf::Vector2f calculatedposition; 
		
		do {
			calculatedposition.x = rand() % 1500 + 200;
			calculatedposition.y = rand() % 1500 + 200;
		} while (!Overlapping(map, calculatedposition, ID));

		AdjustTileMap(map, calculatedposition, ID);
		
		return calculatedposition;
	}

	void AdjustTileMap(MapGenerator& map, const sf::Vector2f &calculatedposition, Textures::ID ID)
	{
		sf::Vector2f tilesize = static_cast<sf::Vector2f>(map.GetTileSize());
		int startX = calculatedposition.x / tilesize.x, endX = GetTextureSize(ID).x / tilesize.x;
		int startY = calculatedposition.y / tilesize.y, endY = GetTextureSize(ID).y / tilesize.y;
		int range = 3; 

		for (int i = startX; i < startX + endX+range-2; i++) {
			for (int j = startY+1; j < startY + endY + range-2; j++)
			{
				map.p_tileMap[i][j].occupied = true; 
				map.p_tileMap[i][j].occupationID = ID; 

				map.p_tileMap[i][j].tile_sprite.setColor(sf::Color::Red); 
			}
		}
	}

	bool Overlapping(MapGenerator& map, const sf::Vector2f& calculatedposition, Textures::ID ID) {
		sf::Vector2f tilesize = static_cast<sf::Vector2f>(map.GetTileSize());
		int startX = calculatedposition.x / tilesize.x, endX = GetTextureSize(ID).x / tilesize.x;
		int startY = calculatedposition.y / tilesize.y, endY = GetTextureSize(ID).y / tilesize.y;
	
		for (int i = startX; i < startX + endX; i++) {
			for (int j = startY; j < startY + endY; j++)
			{
				if (map.p_tileMap[i][j].occupied == true) {
					return false; 
				}
			}
		}
		return true; 
	}

	bool EntityIsOverlapping(const sf::Vector2f &position)
	{
		sf::RectangleShape hypotheticalHitbox; hypotheticalHitbox.setPosition(position); 
		for (int i = 0; i < p_entities.size() - 1; i++) {
			if (CollisionCheck(hypotheticalHitbox.getGlobalBounds(),
				p_entities[i]->p_hitbox.getGlobalBounds()))
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
			return sf::Vector2f(110, 150);
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

public: 
	std::vector<Spawner*> p_spawners;
	std::vector<Entity*>  p_entities;
	std::vector<Item*>	 p_items;

private: 
	std::vector<Spawner> notavectorofspawners;
	sf::Clock m_clock; 
	int m_timer = 500;

};

