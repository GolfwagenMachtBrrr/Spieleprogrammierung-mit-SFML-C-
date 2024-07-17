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
		std::cout << "FAILED to LOAD tileSHEET !" << std::endl;
	}

}

//.........................


void MapGenerator::Initialize()
{
	// Werte nach tutorial: -
	// Einstellungen der einzelnen Waves sollen später via Engine hinzugefügt werden können.
	// Momentan : (HeightMap, HeatMap, MoistureMap)  

	m_biomeSetter.Initialize();

	m_prop1Waves.push_back(Wave(56, 0.05, 1));
	m_prop1Waves.push_back(Wave(199.36, 0.1, 0.5));

	m_prop2Waves.push_back(Wave(621, 0.03, 1));

	m_prop3Waves.push_back(Wave(318, 0.04, 1));
	m_prop3Waves.push_back(Wave(329.7, 0.02, 0.5));

	if (!m_tileMap.load(m_tileSheet)) {
		std::cout << "failed to tilesheet - (TileMap.h)" << std::endl;
	}

	LoadTexture(m_tileSheet, m_texture); 
}

void MapGenerator::Generate()
{
	m_height = 100, m_width = 100; 

	m_prop1 = m_noiseGen.Generate(m_width, m_height,1, m_prop1Waves, m_offset);
	m_prop2 = m_noiseGen.Generate(m_width, m_height,1, m_prop2Waves, m_offset);
	m_prop3 = m_noiseGen.Generate(m_width, m_height,1, m_prop3Waves, m_offset);

	for (int i = 0; i < m_width; i++)
	{
		for (int j = 0; j < m_height; j++)
		{
			int index = j + i * m_height;
			m_tileField.push_back(m_biomeSetter.GetBiome(m_prop1[index], m_prop2[index], m_prop3[index]));
		}
	}
}
// https://gist.github.com/lxndrdagreat/da4400e23ac611ec3567






void MapGenerator::Update(Camera &camera, sf::View &gameView, sf::RenderWindow& Window)
{

	// TODO: -> Rendern funktioniert noch noch nicht richtig
	// FALLS -> TileMap.h verwendet wird - Klassen variablen zurücksetzten nach DRAW call

	// EXP? 
	int cPosX = camera.GetPosition().x; 
	int cPosY = camera.GetPosition().y;
	int range = 3; 

	std::cout << camera.GetPosition().x << " " << camera.GetPosition().y << std::endl; 

	for (int dx = -range; dx < range; dx++) {
		for (int dy = -range; dy < range; dy++)
		{
			int tx = (cPosX + dx + m_width) % m_width;
			int ty = (cPosY + dy + m_height) % m_height; 


			int i_tile; 

			if (tx == 0 || ty == 0) {
				i_tile = tx + ty; 
			}
			else
			{
				i_tile = tx * ty; 
			}

			int tilenumber = m_tileField[i_tile]; 

			sf::Sprite sprite; 

			sprite.setTexture(m_texture);
			sprite.setTextureRect(sf::IntRect(0,0,m_tileSize.x * tilenumber, m_tileSize.y));
			sprite.setPosition(sf::Vector2f(tx * m_tileSize.x, ty * m_tileSize.y));

			Window.draw(sprite);
		}
	}



	// EXP !

	// Ich brauch ein  FROM - TO system 
	int fromX = std::max(0, (int)camera.GetPosition().x - 2) / m_tileSize.x; 
	int fromY = std::max(0, (int)camera.GetPosition().y - 2) / m_tileSize.y;
	int toX = std::min(m_width - 1, (int)camera.GetPosition().x + 2);
	int toY = std::min(m_height - 1, ((int)camera.GetPosition().y + 2));
	 
	
	//std::cout << fromX << " " << fromY << " " << toX << " " << toY << "  " << std::endl; 

	//m_tileMap.CreateTileMap(m_tileSheet, m_tileSize, m_tileField, fromX, fromY, toX, toY);
}


void MapGenerator::Draw(sf::RenderWindow &Window)
{
	//Window.draw(m_tileMap);

}

