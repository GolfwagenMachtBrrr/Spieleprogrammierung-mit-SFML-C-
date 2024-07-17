#include "Grid_Gen.h"

void GridGenerator::Initalize(sf::RenderWindow& window)
{
	int tilesX = window.getSize().x / imageSizeX;
	int tilesY = window.getSize().y / imageSizeY;

	for (int i = 0; i < tilesX; i++) {
		sf::RectangleShape grid_unit = sf::RectangleShape(sf::Vector2f(window.getSize().x, 2));
		grid_unit.setPosition(0, imageSizeX * i);
		grid_unit.setFillColor(sf::Color::White);
		grid_row.push_back(grid_unit);

	}
	for (int i = 0; i < tilesY; i++) {
		sf::RectangleShape grid_unit = sf::RectangleShape(sf::Vector2f(2, window.getSize().y));
		grid_unit.setPosition(imageSizeY * i, 0);
		grid_unit.setFillColor(sf::Color::White);
		grid_column.push_back(grid_unit);
	}
}


void GridGenerator::Update()
{
}

void GridGenerator::Draw(sf::RenderWindow& window)
{
	for (auto i : grid_row)
	{
		window.draw(i);
	}
	for (auto j : grid_column)
	{
		window.draw(j);
	}
}
