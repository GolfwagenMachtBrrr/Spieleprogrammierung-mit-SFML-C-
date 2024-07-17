#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Network.hpp>

#include <iostream>
#include <vector>

class GridGenerator
{
private: 

	std::vector<sf::RectangleShape> grid_row;
	std::vector<sf::RectangleShape> grid_column;

	int imageSizeX;
	int imageSizeY;

public: 
	void Initalize(sf::RenderWindow& window);
	void Update();
	void Draw(sf::RenderWindow& window);

	GridGenerator()
		: imageSizeX(64), imageSizeY(64)
	{}

};

