#pragma once
#include <SFML/Graphics.hpp>

#include "NoizeGenerator.h"
#include "BiomSetter.h"
#include "Tile.h"
#include "Viewer.h"
#include "ResourceHolder.h"
#include <iostream>
#include <vector>


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
		m_width = width; m_width = 100;
		m_height = height; m_height = 100;


		m_biomeSetter.Initialize();
		m_noise.Initialize(m_width, m_height, 1, sf::Vector2f(0, 0));
	}
	void Generate()
	{
		m_height = 100, m_width = 100;

		for (int i = 0; i < m_width; i++)
		{
			std::vector<Tile> tileMap_row;
			for (int j = 0; j < m_height; j++)
			{
				int index = j + i * m_height;
				int biome = m_biomeSetter.GetBiome(m_noise.GetBiomValues(index));
 
				sf::IntRect texRect(m_tileSize.x * (biome + 5), 0, m_tileSize.x, m_tileSize.y);
				sf::Vector2f tilePos(m_tileSize.x * i, m_tileSize.y * j);

				Tile tile(index, biome, &texRect, m_tilesprite, tilePos);

				tile.SetupSprite();

				tileMap_row.push_back(tile);
			}
			p_tileMap.push_back(tileMap_row);
		}
	}
	// https://gist.github.com/lxndrdagreat/da4400e23ac611ec3567
	void Update(sf::View& gameView, sf::RenderWindow& Window); // const ?
	void Draw(sf::RenderWindow& Window, Viewer& view)	// const ? 
	{
		int range = 25;

		int fromX = (view.GetPosition().x / m_tileSize.x) - range;
		int fromY = (view.GetPosition().y / m_tileSize.y) - range;

		int toX = (view.GetPosition().x / m_tileSize.x) + range;
		int toY = (view.GetPosition().y / m_tileSize.y) + range;

		//std::cout << fromX << " " << toX << " " << fromY << " " << toY << std::endl; 

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

	const sf::Vector2u GetTileSize()
	{
		return m_tileSize; 
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

