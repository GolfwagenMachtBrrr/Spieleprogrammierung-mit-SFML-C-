#pragma once
#include <SFML/Graphics.hpp>

#include "NoizeGenerator.h"
#include "BiomSetter.h"
#include "Tile.h"
#include "Viewer.h"
#include "TextureHolder.h"


#include <iostream>
#include <vector>


class MapGenerator
{
public: 

	void Initialize(const sf::Vector2u& tilesize, const std::string& tilesheet, const int& width, const int& height);
	void Generate();
	void Update(sf::View& gameView, sf::RenderWindow& Window); // const ?
	void Draw(sf::RenderWindow &Window, Viewer& view); // const ? 

private:

	int m_width;  
	int m_height;

	BiomeSetter m_biomeSetter;
	NoizeGenerator m_noise;
	TextureHolder m_textureholder; 

	sf::Texture m_texture;
	std::string m_tileSheet;
	sf::Vector2u m_tileSize;

	std::vector <std::vector<Tile>> m_tileMap; 
};

