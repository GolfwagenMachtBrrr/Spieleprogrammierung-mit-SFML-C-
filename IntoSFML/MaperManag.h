#pragma once
#include "Spawner.h"
#include "Building.h"
#include "MapGenerator.h"
#include "Gun.h"

#include "nCollision.h"

class MaperManag
{
public:
	void Initialize()
	{
		// Player
		m_player = new Player(Textures::ID::Player, Fonts::ID::OnlyFont, sf::Vector2f(400, 300), sf::IntRect(0, 0, 64, 64));
		Collisions::_CollisionManager.addObject(m_player);

		//Map
		m_map = new MapGenerator();
		int width = 1920 / GameData::_TileSize.x, height = 1080 / GameData::_TileSize.y;
		m_map->Initialize(GameData::_TileSize, width, height);
		m_map->Generate();

		//Game Objects
		InitHouses(20);
		InitSpawner(1, 5);

		// View
		m_gameview.zoom(0.3);
	}
	void Update()
	{
		// Calculating deltatime
		m_deltatimer.CalculateDeltaTime();
		m_dt = m_deltatimer.GetDeltatime();

		//Updateing GameObjects
		m_player->Update();

		for (auto& spawner : m_spawners) { spawner->mUpdate(m_deltatimer.GetDeltatime(), m_player->GetPosition()); }

		UpdateBuildings();

		// Collisions
		Collisions::_CollisionManager.checkCollisions();
	}
	void Draw(sf::RenderWindow& window)
	{
		m_gameview.setCenter(m_player->GetPosition());
		window.setView(m_gameview);

		m_map->Draw(window, m_player->GetPosition());

		for (auto& spawner : m_spawners) { spawner->Draw(window); }
		for (auto& entity : m_buildings) { entity->Draw(window); }

		m_player->Draw(window);
	}

private:
	void InitSpawner(const int amount, const int density)
	{
		for (int i = 0; i < amount; i++)
		{
			Spawner* spawner = new Spawner(Textures::ID::Spawner, Fonts::ID::OnlyFont, CalculatePosition(m_map, Textures::ID::Spawner), i);
			m_spawners.push_back(spawner);
		}

		for (int i = 0; i < amount; i++) {
			std::vector<Textures::ID> spawntypes;
			for (int j = 0; j < density; j++) { spawntypes.push_back(Textures::ID::Zombie); }
			m_spawners[i]->AddToStack(spawntypes);
		}
	}
	void InitHouses(const int amount)
	{
		int latestIndex = m_buildings.size() - 1;
		for (int i = 0; i < amount; i++) {
			// Houses Setup
			sf::Vector2f newposition = CalculatePosition(m_map, Textures::ID::House);
			Building* house = new Building(Textures::ID::House, Fonts::ID::OnlyFont, newposition);

			Collisions::_CollisionManager.addObject(house);
			m_buildings.push_back(house);
		}
	}
	void InitItems(const Textures::ID tID, const Fonts::ID fID, const sf::Vector2f& InitialPosition)
	{
		switch (tID)
		{
		case Textures::ID::Wand:
			m_gun = new Gun(tID, fID, InitialPosition);
			m_gun->interactive = true;
			m_items.push_back(m_gun);

		default:
			break;
		}
	}

	void UpdateBuildings()
	{
		for (auto& spawner : m_spawners) { spawner->mUpdate(m_dt, m_player->GetPosition()); }
		for (auto& building : m_buildings) { building->Update(); }
		for (auto& item : m_items) { item->Update(); }
	}
private:
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
	void AdjustTileMap(MapGenerator* map, const sf::Vector2f& calculatedposition, Textures::ID ID)
	{
		sf::Vector2f tilesize = static_cast<sf::Vector2f>(GameData::_TileSize);
		int startX = calculatedposition.x / tilesize.x, endX = GetTextureSize(ID).x / tilesize.x;
		int startY = calculatedposition.y / tilesize.y, endY = GetTextureSize(ID).y / tilesize.y;
		int range = 0;

		for (int i = startX; i < startX + endX + range; i++) {
			for (int j = startY; j < startY + endY + range; j++)
			{
				map->p_tileMap[i][j].occupied = true;
				map->p_tileMap[i][j].occupationID = ID;
			}
		}
	}
	bool Overlapping(MapGenerator* map, const sf::Vector2f& calculatedposition, Textures::ID ID)
	{
		sf::Vector2f tilesize = static_cast<sf::Vector2f>(GameData::_TileSize);
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
	const sf::Vector2f GetTextureSize(Textures::ID tID)
	{
		switch (tID) {
		case Textures::ID::House:
			return sf::Vector2f(110, 150);
		case Textures::ID::Spawner:
			return sf::Vector2f(100, 80);
		}
	}


private:
	std::vector<Spawner*>   m_spawners;
	std::vector<Building*>  m_buildings;
	std::vector<Item*>	    m_items;

	MapGenerator* m_map;
	Player* m_player;
	Gun* m_gun;

	sf::View      m_gameview;
	Timer		  m_deltatimer;

	float m_dt;
public:
};

