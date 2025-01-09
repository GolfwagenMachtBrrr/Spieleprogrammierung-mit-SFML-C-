#pragma once
#include "Spawner.h"
#include "Building.h"
#include "MapGenerator.h"
#include "Gun.h"

#include "nCollision.h"

class MapMaker
{
public:
	MapMaker(){}

	void Initialize()
	{
		// Player
		m_player =  std::make_unique<Player>(Textures::ID::Player, Fonts::ID::OnlyFont, sf::Vector2f(400, 300), sf::IntRect(0, 0, 64, 64));
		Collisions::_CollisionManager.addObject(m_player);

		//Map
		m_map = std::make_unique<MapGenerator>(); 
		int width = 1920 / GameData::_TileSize.x, height = 1080 / GameData::_TileSize.y;
		m_map->Initialize(GameData::_TileSize, width, height);
		m_map->Generate();

		//Game Objects
		//InitHouses(20);
		//InitSpawner(1, 5);

		// View
		m_gameview.zoom(1);
	}
	void Update()
	{
		// Calculating deltatime
		m_deltatimer.CalculateDeltaTime();
		GameData::_DeltaTime = m_dt = m_deltatimer.GetDeltatime();
		

		//Updateing GameObjects
		m_player->Update();

		for (auto& spawner : m_spawners) { spawner->Update(m_deltatimer.GetDeltatime(), m_player->GetPosition()); }

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
		m_gun.Draw(window);
	}

private:
	void InitSpawner(const int amount, const int density)
	{
		for (int i = 0; i < amount; i++)
		{
			std::shared_ptr<Spawner> spawner = std::make_shared<Spawner>(Textures::ID::Spawner, Fonts::ID::OnlyFont, CalculatePosition(m_map, Textures::ID::Spawner), i);
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
			std::shared_ptr<Building> house =  std::make_shared<Building>(Textures::ID::House, Fonts::ID::OnlyFont, newposition);

			Collisions::_CollisionManager.addObject(house);
			m_buildings.push_back(house);
		}
	}
	void InitItems(const Textures::ID tID, const Fonts::ID fID, const sf::Vector2f& InitialPosition)
	{
		switch (tID)
		{
		case Textures::ID::Wand:
			m_gun = Gun(tID, fID, InitialPosition);
			m_gun.interactive = true;
			m_items.push_back(m_gun);

		default:
			break;
		}
	}

	void UpdateBuildings()
	{
		for (auto& spawner : m_spawners) { spawner->Update(m_dt, m_player->GetPosition()); }
		m_gun.Update(); 

	}
private:
	sf::Vector2f CalculatePosition(std::shared_ptr<MapGenerator> map, Textures::ID ID)
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
	void AdjustTileMap(std::shared_ptr<MapGenerator> map, const sf::Vector2f& calculatedposition, Textures::ID ID)
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
	bool Overlapping(std::shared_ptr<MapGenerator> map, const sf::Vector2f& calculatedposition, Textures::ID ID)
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
	std::vector<std::shared_ptr<Spawner>>   m_spawners;
	std::vector<std::shared_ptr<Building>>  m_buildings;
	//std::vector<std::shared_ptr<Item>>	    m_items;

	//std::shared_ptr<Gun>		  m_gun;
	std::shared_ptr<Player>		  m_player;

	std::shared_ptr<MapGenerator> m_map;

	Gun m_gun; 
	std::vector<Item> m_items; 

	sf::View      m_gameview;
	Timer		  m_deltatimer;

	float m_dt;
public:
};

