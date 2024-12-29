#pragma once
#include "Common.h"

#include "NoizeGenerator.h"
#include "BiomSetter.h"
#include "Tile.h"


#include "nRessources.h"
#include "nGameData.h"

// https://gist.github.com/lxndrdagreat/da4400e23ac611ec3567

class MapGenerator
{
public: 

	MapGenerator()
	{}

	void Initialize(const sf::Vector2u& tilesize, const int& width, const int& height)
	{
		m_tilesprite.setTexture(Textures::_TextureHolder.Get(Textures::ID::Grass));
		m_width = width * 4;
		m_height = height * 4;

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

				sf::IntRect texRect(GameData::_TileSize.x * (biome + 5), GameData::_TileSize.y * (biome + 10), GameData::_TileSize.x, GameData::_TileSize.y);
				sf::Vector2f tilePos(GameData::_TileSize.x * i, GameData::_TileSize.y * j);

				Tile tile(index, biome, &texRect, m_tilesprite, tilePos);

				tileMap_row.push_back(tile);
			}
			p_tileMap.push_back(tileMap_row);
		}
	}
	void Draw(sf::RenderWindow& Window, const sf::Vector2f& player_position)
	{
		int range = GameData::_RenderRange;

		int fromX = (player_position.x / GameData::_TileSize.x) - range;
		int fromY = (player_position.y / GameData::_TileSize.y) - range;

		int toX = (player_position.x / GameData::_TileSize.x) + range;
		int toY = (player_position.y / GameData::_TileSize.y) + range;


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
	
	sf::Vector2f GetMapSize() const noexcept { return sf::Vector2f(m_width, m_height); }

public:
	std::vector<std::vector<Tile>> p_tileMap;

private:
	int m_width, m_height;

	BiomeSetter m_biomeSetter;
	NoizeGenerator m_noise;

	sf::Sprite m_tilesprite; 
};


