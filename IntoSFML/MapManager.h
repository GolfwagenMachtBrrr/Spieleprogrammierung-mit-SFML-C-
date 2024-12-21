#pragma once
#include "SFML/Graphics.hpp"
#include "TimeObject.h"

#include "ResourceHolder.h"
#include "CollisionManager.h"

#include "Building.h" 
#include "Item.h"

#include "Spawner.h"
#include "Player.h"
#include "MapGenerator.h"



#include <random>
#include <vector>


class MapManager : public TimeObject
{
public: 
	void Initialize(const TextureHolder& textures, const sf::Vector2u tilesize)
	{
		// Collisionsmanager
		m_collisionmanager = new CollisionManager();

		// Player
		p_player = new Player(); 
		p_player->Initalize(textures);
		p_player->objectType = Textures::ID::Player;
		m_collisionmanager->addObject(p_player);

		//Map
		p_map = new MapGenerator(); 
		p_map->Initialize(tilesize, textures, 1920 / tilesize.x, 1080 / tilesize.y); 
		p_map->Generate(); 

		//Game Objects
		InitHouses(textures, 10);
		InitSpawner(textures, 1, 2);
	}
	void Update(const sf::Vector2f& convertedmousepos, const TextureHolder& textures)
	{
		// Calculating deltatime
		CalculateDeltatime(); 

		//Updateing GameObjects
		p_player->Update(m_deltatime, convertedmousepos, m_collisionmanager);

		for (auto& spawner :m_spawners) { spawner->Update(m_deltatime, p_player, textures, m_collisionmanager); }

		// Collisions
		m_collisionmanager->checkCollisions(); 
	}
	void Draw(sf::RenderWindow& window)
	{ 
		p_view.setCenter(p_player->GetPosition());
		window.setView(p_view);

		p_map->Draw(window, p_player); 
		p_player->Draw(window); 

		for(auto& spawner : m_spawners) { spawner->Draw(window, p_player); }
		for (auto& entity : m_buildings) { entity->Draw(window, p_player);	}
	}

	void AddSpawner(const int& amount); 
	void AddEntities(Textures::ID ID, const int& amount); 

private: 
	void InitSpawner(const TextureHolder& textures, const int& amount, const int& density)
	{
		for (int i = 0; i < amount; i++) { Spawner* spawner = new Spawner(); m_spawners.push_back(spawner); }
		for (auto& spawner : m_spawners) {
			std::vector<Textures::ID> spawntypes; 
			for (int i = 0; i < density; i++) { spawntypes.push_back(Textures::ID::Zombie); }
			spawner->Initialize(CalculatePosition(p_map, Textures::ID::Spawner), spawntypes, textures, m_collisionmanager);
		}
	}
	void InitHouses(const TextureHolder& textures, const int& amount)
	{
		int latestIndex = m_buildings.size() - 1;
		for (int i = 0; i < amount; i++) {
			// Houses Setup
			sf::Vector2f newposition = CalculatePosition(p_map, Textures::ID::House);
			Building* house = new Building(textures,
										Textures::ID::House, 
										GetTextureSize(Textures::ID::House), 
										newposition);
			m_collisionmanager->addObject(house);
			m_buildings.push_back(house);
		}
	}

	sf::Vector2f CalculatePosition(MapGenerator* map, Textures::ID ID)
	{
		sf::Vector2f calculatedposition; 
		
		do {
			calculatedposition.x = rand() % 1490 + 10;
			calculatedposition.y = rand() % 1490 + 10;
			std::cout << calculatedposition.x << " " << calculatedposition.y << std::endl; 

		} while (!Overlapping(map, calculatedposition, ID));

		AdjustTileMap(map, calculatedposition, ID);
		
		return calculatedposition;
	}

	void AdjustTileMap(MapGenerator* map, const sf::Vector2f &calculatedposition, Textures::ID ID)
	{
		sf::Vector2f tilesize = static_cast<sf::Vector2f>(map->GetTileSize());
		int startX = calculatedposition.x / tilesize.x, endX = GetTextureSize(ID).x / tilesize.x;
		int startY = calculatedposition.y / tilesize.y, endY = GetTextureSize(ID).y / tilesize.y;
		int range = 0; 

		for (int i = startX; i < startX + endX+range; i++) {
			for (int j = startY; j < startY + endY + range; j++)
			{
				map->p_tileMap[i][j].occupied = true; 
				map->p_tileMap[i][j].occupationID = ID; 
			}
		}
	}

	bool Overlapping(MapGenerator* map, const sf::Vector2f& calculatedposition, Textures::ID ID) {
		sf::Vector2f tilesize = static_cast<sf::Vector2f>(map->GetTileSize());
		int startX = calculatedposition.x / tilesize.x, endX = GetTextureSize(ID).x / tilesize.x;
		int startY = calculatedposition.y / tilesize.y, endY = GetTextureSize(ID).y / tilesize.y;
	
		if (startX <= 0 || startY <= 0) {
			return false;
		}

		if (endX >= 100 || endY >= 100) {
			return false;
		}

		if (startX + endX >= 100 || startY + endY >= 100) {
			return false; 
		}

		for (int i = startX; i < startX + endX; i++) {
			for (int j = startY; j < startY + endY; j++)
			{
				if (map->p_tileMap[i][j].occupied == true) {
					return false; 
				}
			}
		}

		return true; 
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

	void CalculateDeltatime()
	{
		m_deltatime = m_deltatimeclock.getElapsedTime().asMilliseconds();
		if (m_deltatime != 0) {
			m_deltatimeclock.restart();
		}
	}

public:
	MapGenerator* p_map;
	Player*       p_player;
	sf::View      p_view;

private: 
	std::vector<Spawner*>   m_spawners;
	std::vector<Building*>  m_buildings;
	std::vector<Item*>	    m_items;

	CollisionManager* m_collisionmanager; 

private:
	sf::Clock m_deltatimeclock; 
	float     m_deltatime;
};

