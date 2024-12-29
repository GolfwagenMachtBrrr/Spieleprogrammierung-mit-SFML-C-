#include "SFML/Window.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <SFML/Network.hpp>

#include"GameWindow.h"


//https://gamedevacademy.org/procedural-2d-maps-unity-tutorial/
//https://www.sfml-dev.org/tutorials/2.6/graphics-view.php


//void test_astar_with_labyrinth()
//{
//    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Pathfinding");
//
//    const int width = 1920 / 16, height = 1080 / 16;
//
//    std::vector<std::vector<Algorithms::tile>> grid;
//
//    for (int x = 0; x < width; x++) {
//        std::vector<Algorithms::tile> tiles;
//        for (int y = 0; y < height; y++)
//        {
//            Algorithms::tile cell;
//
//            cell.enabled = false;
//            cell.x = x;
//            cell.y = y;
//
//            cell.box = sf::RectangleShape(sf::Vector2f(16, 16));
//
//            cell.box.setFillColor(sf::Color::White);
//            cell.box.setOutlineColor(sf::Color::Black);
//            cell.box.setOutlineThickness(1);
//            cell.box.setPosition(sf::Vector2f(cell.x * 16, cell.y * 16));
//
//            tiles.push_back(cell);
//        }
//        grid.push_back(tiles);
//    }
//
//    sf::Vector2f start(1 + (int)(width * (rand() / (RAND_MAX + 1.0))), 1 + (int)(height * (rand() / (RAND_MAX + 1.0))));
//    sf::Vector2f dest(1 + (int)(width * (rand() / (RAND_MAX + 1.0))), 1 + (int)(height * (rand() / (RAND_MAX + 1.0))));
//
//    grid[(int)start.x][(int)start.y].box.setFillColor(sf::Color::Green);
//    grid[(int)dest.x][(int)dest.y].box.setFillColor(sf::Color::Red);
//
//    Algorithms::Astar astar;
//
//    while (window.isOpen())
//    {
//        // Process events
//        sf::Event event;
//        while (window.pollEvent(event))
//        {
//            // Close window: exit
//            if (event.type == sf::Event::Closed)
//                window.close();
//        }
//
//        astar.Search(grid[(int)start.x][(int)start.y], grid[(int)dest.x][(int)dest.y], grid, window);
//
//        window.display();
//
//        sf::sleep(sf::microseconds(1));
//    }
//
//}

int main()
 {
    GameWindow gw; 
    gw.Start(); 
    return 0;
}