#include "MapGenerator.h"

// FOR EXPERIMENTATION
float average(float** arr, int sizeX, int sizeY)
{
	float tmp = 0;
	for (int i = 0; i < sizeX; i++)
	{
		for (int j = 0; j < sizeY; j++) {
			tmp += arr[i][j];
		}
	}
	tmp /= (sizeX * sizeY); 
	return tmp; 
}

void LoadTexture(const std::string& tileSheet, sf::Texture& texture)
{
	if (!texture.loadFromFile(tileSheet)) {
		std::cout << "MapGenerator.cpp -> LoadTexture()" << std::endl;
	}

}

//.........................


void MapGenerator::Initialize(const sf::Vector2u &tilesize, const std::string& tilesheet, const int &width, const int& height)
{
	this->m_tileSize = tilesize;
	this->m_tileSheet = tilesheet;
	this->m_width = width; m_width = 100; 
	this->m_height = height; m_height = 100; 


	m_biomeSetter.Initialize();
	m_noise.Initialize(m_width, m_height, 1, sf::Vector2f(0,0));

	m_texture = m_textureholder.GetTexture("tileset_grass");
}

void MapGenerator::Generate()
{
	m_height = 100, m_width = 100; 

	for (int i = 0; i < m_width; i++)
	{
		std::vector<Tile> tileMap_row; 
		for (int j = 0; j < m_height; j++)
		{
			int index = j + i * m_height;
			int biome = m_biomeSetter.GetBiome(m_noise.GetBiomValues(index));
	
			sf::IntRect texRect(m_tileSize.x * (biome + 5) , 0, m_tileSize.x, m_tileSize.y);
			sf::Vector2f tilePos(m_tileSize.x * i, m_tileSize.y * j);

			Tile tile(index, biome, &m_texture, &texRect, tilePos);

			tile.SetupSprite(); 
				
			tileMap_row.push_back(tile);
		}
		m_tileMap.push_back(tileMap_row);
	}
}
// https://gist.github.com/lxndrdagreat/da4400e23ac611ec3567


void MapGenerator::Update(sf::View &gameView, sf::RenderWindow& Window)
{

}


void MapGenerator::Draw(sf::RenderWindow &Window, Viewer &view)
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
			Window.draw(m_tileMap[i][j].tile_sprite);
		}
	}
}

