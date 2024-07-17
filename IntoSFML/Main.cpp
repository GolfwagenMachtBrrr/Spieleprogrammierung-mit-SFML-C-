#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Network.hpp>


#include "Grid_Gen.h"
#include "MapGenerator.h"
#include "NoizeGenerator.h"
#include "Camera.h"
#include <iostream>
#include <random>

//https://gamedevacademy.org/procedural-2d-maps-unity-tutorial/
//https://www.sfml-dev.org/tutorials/2.6/graphics-view.php

int main()
{
    std::string tilesheet = "C:/Users/JanSa/OneDrive/Desktop/Programmieren/Projekte/ProcMapGen/Game/Assets/World/NumsVer3.png";
    sf::Vector2u tmpVec(25,40); 
    sf::RenderWindow window(sf::VideoMode(25*40, 40*25), "SFML window");

   
    sf::View gameView = window.getDefaultView(); 
    sf::View miniMapView= window.getDefaultView();

    gameView.setViewport(sf::FloatRect(0, 0, 1, 1));
    miniMapView.setViewport(sf::FloatRect(0.75, 0, 0.25, 0.25));

    gameView.zoom(0.1);

    Camera camera(0.125/10);
    GridGenerator gridgen;
    MapGenerator mapgen(window, tmpVec, tilesheet); 

    mapgen.Initialize(); 
    gridgen.Initalize(window);

    // Generate
    mapgen.Generate();

    // DeltaTime
    sf::Clock clock; 
    // Start the game loop

    while (window.isOpen())
    {
        // Calculate DeltaTime
        sf::Time deltatimetimer = clock.restart();
        float deltatime = deltatimetimer.asMilliseconds();

        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::Resized)
            {
                // update the view to the new size of the window
                sf::FloatRect visibleArea(0.f, 0.f, event.size.width/2, event.size.height/2);
                window.setView(sf::View(visibleArea));
            }
        }
       // std::cout << gameView.getSize().x << " " << gameView.getSize().x << std::endl; 

        camera.Update(deltatime);
        window.clear();
        mapgen.Update(camera, gameView, window);
        gameView.setCenter(camera.GetPosition());
        window.setView(gameView);
        mapgen.Draw(window);
       // window.setView(miniMapView);
        mapgen.Draw(window);
        window.display();
    }

    return EXIT_SUCCESS;
}