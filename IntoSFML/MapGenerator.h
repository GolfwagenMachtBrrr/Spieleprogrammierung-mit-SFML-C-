#pragma once
#include <SFML/Graphics.hpp>

#include "NoizeGenerator.h"
#include "BiomSetter.h"
#include "Tile.h"
#include "Viewer.h"
#include "ResourceHolder.h"
#include <iostream>
#include <vector>
#include "Player.h"


typedef ResourceHolder<sf::Texture, Textures::ID> TextureHolder;

class MapGenerator
{
public: 

	MapGenerator()
	{}

	void Initialize(const sf::Vector2u& tilesize, const TextureHolder& textures, const int& width, const int& height)
	{
		m_tilesprite.setTexture(textures.Get(Textures::ID::Grass));
		m_tileSize = tilesize;
		m_width = width*4; 
		m_height = height*4; 

		m_biomeSetter.Initialize();
		m_noise.Initialize(m_width, m_height, 1, sf::Vector2f(0, 0));
	}
	void Generate()
	{
		for (int i = 0; i < m_width; i++)
		{
			std::vector<Tile> tileMap_row;
			for (int j = 0; j < m_height; j++)
			{
				int index = j + i * m_height;
				int biome = m_biomeSetter.GetBiome(m_noise.GetBiomValues(index));
 
				sf::IntRect texRect(m_tileSize.x * (biome + 5), m_tileSize.y * (biome + 10), m_tileSize.x, m_tileSize.y);
				sf::Vector2f tilePos(m_tileSize.x * i, m_tileSize.y * j);

				Tile tile(index, biome, &texRect, m_tilesprite, tilePos);

				tileMap_row.push_back(tile);
			}
			p_tileMap.push_back(tileMap_row);
		}
	}
	// https://gist.github.com/lxndrdagreat/da4400e23ac611ec3567
	
	void Draw(sf::RenderWindow& Window, Player* player)	// const ? 
	{
		int range = GameData::data_renderrange;

		int fromX = (player->GetPosition().x / m_tileSize.x) - range;
		int fromY = (player->GetPosition().y / m_tileSize.y) - range;

		int toX = (player->GetPosition().x / m_tileSize.x) + range;
		int toY = (player->GetPosition().y / m_tileSize.y) + range;


		if (fromX < 0)
			fromX = 0;
		if (toX >= m_width)
			toX = m_width - 1;

		if (fromY < 0)
			fromY = 0;
		if (toY >= m_height)
			toY = m_height - 1;


		for (int i = fromX; i < toX; i++)
		{
			for (int j = fromY; j < toY; j++)
			{
				Window.draw(p_tileMap[i][j].tile_sprite);
			}
		}
	}

	sf::Vector2u GetTileSize() const
	{
		return m_tileSize; 
	}

	sf::Vector2f GetMapSize() const
	{
		return sf::Vector2f(m_width, m_height);
	}

public:
	std::vector<std::vector<Tile>> p_tileMap;

private:
	int m_width;  
	int m_height;

	BiomeSetter m_biomeSetter;
	NoizeGenerator m_noise;

	sf::Sprite m_tilesprite; 
	std::string m_tileSheet;
	sf::Vector2u m_tileSize;

};


