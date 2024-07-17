#pragma once
#include "NoizeGenerator.h"
#include "BiomSetter.h"
#include "TileMap.h"
#include "Camera.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

class MapGenerator
{
public: 

	MapGenerator(const sf::RenderWindow &Window, const sf::Vector2u &TileSize, const std::string &TileSheet)
		: m_width(Window.getSize().x / TileSize.x), m_height(Window.getSize().y / TileSize.y), m_tileSize(TileSize), m_tileSheet(TileSheet)
	{}

	void Initialize();
	void Generate();
	void Update(Camera &camera, sf::View& gameView, sf::RenderWindow& Window); // const ?
	void Draw(sf::RenderWindow &Window); // const ? 

private:

	int m_width, m_height;

	std::vector<int> m_tileField;

	std::vector<float> m_prop1;
	std::vector<float> m_prop2;
	std::vector<float> m_prop3;

	std::vector<Wave> m_prop1Waves;
	std::vector<Wave> m_prop2Waves;
	std::vector<Wave> m_prop3Waves;

	BiomeSetter m_biomeSetter;
	NoizeGenerator m_noiseGen;
	TileMap m_tileMap;


	sf::Texture m_texture;

	std::string m_tileSheet;
	sf::Vector2f m_offset;
	sf::Vector2u m_tileSize;

	std::vector<sf::Vector2f> m_memory_Destroyer;

};

