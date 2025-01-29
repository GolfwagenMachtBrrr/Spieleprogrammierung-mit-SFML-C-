#pragma once
#include "MapDataManager.h"
#include "SFML/Graphics.hpp"

#include "Common.h"

class Grid
{
public:
	void Initialize(int hCells, int vCells)
	{
		/*int hCells = m_width / GameData::_TileSize.x;
		int vCells = m_height / GameData::_TileSize.y;*/

		m_tcells = hCells * vCells;
		m_gridinfo = new GridInfo[m_tcells];
		m_gridsprites = new sf::Sprite[m_tcells];

		m_backgroundImage.create(1920*4, 1080*4);
		//Fill? 
		/*for (int x = 0; x < hCells; x++) {
			for (int y = 0; y < vCells; y++) {
				m_backgroundImage.setPixel(x, y, sf::Color::Black);
			}
		}*/

		for (int x = 0; x < hCells*32; x += 32)
		{
			for (int y = 0; y < vCells*16; y++)
			{
				m_backgroundImage.setPixel(x, y, sf::Color::Cyan);
			}
		}

		/*for (size_t x = 0; x < hCells; x++)
		{
			for (size_t y = 0; y < vCells; y++)
			{
				int index = y + x * vCells; 
				m_backgroundImage.setPixel(x * 16, y * 16, sf::Color::White);
				m_gridinfo[index].position = new Vector2f(x * 32, y * 32); 

			}
		}*/
	}

	void Update()
	{

	}

	void Draw(sf::RenderWindow& window)
	{
		m_backgroundTexture.loadFromImage(m_backgroundImage);
		m_backgroundSprite.setTexture(m_backgroundTexture);
		window.draw(m_backgroundSprite);

		for (int i = 0; i < m_tcells; i++)
		{
			window.draw(m_gridsprites[i]);
		}
	}

	void GetGridData();
	void ResetGrid();
	void FillGrid();

public:
	struct GridInfo
	{
		short int RectID = -1;
		Textures::ID tID = Textures::ID::Undefined;

		bool isChangeable = true;

		sf::Texture* texture = nullptr;
		sf::IntRect* intRect = nullptr;

		Vector2f*	position; 
	};

private:
	sf::Image			m_backgroundImage;
	sf::Texture			m_backgroundTexture;
	sf::Sprite			m_backgroundSprite;

	sf::Sprite* m_gridsprites;
	sf::Vector2f* m_gridpoints;

	GridInfo* m_gridinfo;
	MapDataManager		m_mapdata;

	int m_width, m_height;
	int m_lastmode;
	int m_tcells;

};

class MapEditor
{
public: 
	void Start()
	{
		this->InitFont();
		this->InitWindow();
		this->InitTextures();
		this->MenuLoop();
	}

	void InitFont()
	{
	}
	void InitTextures()
	{

	}
	void InitWindow()
	{
		this->m_window.create(sf::VideoMode(m_width, m_height), "GameMenu");
		this->m_window.setMouseCursorVisible(true);

		m_grid.Initialize(m_width / GameData::_TileSize.x, m_height / GameData::_TileSize.y);

	}

	void Update()
	{
		m_grid.Update(); 

	}

	void MenuLoop()
	{
		while (m_window.isOpen())
		{
			sf::Event event;
			while (m_window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
				{
					m_window.close();
				}

				m_window.clear(sf::Color::Black); 

				m_grid.Update(); 

				m_grid.Draw(m_window);

				m_window.display(); 

			}
		}
	}

private:
	int						  m_width = 1920;
	int						  m_height = 1080;

	sf::RenderWindow		  m_window;
	MapDataManager			  m_mapdata; 

	Grid m_grid; 

};






