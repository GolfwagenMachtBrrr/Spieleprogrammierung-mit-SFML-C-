#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Network.hpp>


#include "MapGenerator.h"
#include "NoizeGenerator.h"
#include "Player.h"
#include "Gun.h"
#include "TextureHolder.h"
#include "Inventory.h"
#include "EnemyManager.h"
#include "Spawner.h"

#include <iostream>
#include <random>


class GameWindow
{
public:

    void Start(bool start)
    {
        if (start)
        {
            this->InitEnemyManager();
            this->InitWindow();
            this->InitPlayer(); 
            this->IntitOtherValues();
            this->InitMap();
            this->InitViewer();
            this->GameLoop();
        }
    }

    void InitEnemyManager()
    {


        int examplePosX = rand() % 1500,
            examplePosY = rand() % 1000;

        std::vector<Spawner::SpawnType> type; 
        for (int i = 0; i < 10; i++) { type.push_back(Spawner::ZOMBIE); }

        this->m_spawner.Initialize(sf::Vector2f(examplePosX, examplePosY), type, m_textures);
    }

    void IntitOtherValues()
    {
        this->m_tilesheet = "../Assets/World/NumsVer3.png";
        this->m_tilesize.x = 25;
        this->m_tilesize.y = 40;
        this->m_dt = 16;

        // Mouse logic
        m_curor_texture = m_textures.GetTexture("cursor"); 
        this->m_cursor.setTexture(m_curor_texture);

        //Inventory
        
    }

    void InitWindow()
    {
        this->m_window.create(sf::VideoMode(1920, 1080), "GameWindow");
        this->m_window.setMouseCursorVisible(false);
    }

    void InitMap()
    {
        int width = m_window.getSize().x / m_tilesize.x; std::cout << width << std::endl;
        int height = m_window.getSize().y / m_tilesize.y; std::cout << height << std::endl; 

        this->m_inventory.Initialize(m_textures, m_window.getSize().x, m_window.getSize().y);

        this->m_map.Initialize(m_tilesize, m_tilesheet, width, height);
        this->m_map.Generate();
    }

    void InitViewer()
    {
        sf::Vector2f startingPosition(0, 0);
        float speed = 0.125 / 20;
        float zoom = 1;

        this->m_gameview.Initialize(startingPosition, speed, zoom);
    }

    void InitPlayer()
    {
        this->m_player.Initalize(m_textures);
       
       
    }
    
    int GameLoop()
    {
        while (m_window.isOpen())
        {
            // Calculate DeltaTime
            m_dt = 16;

            // Process events
            sf::Event event;
            while (m_window.pollEvent(event))
            {
                // Close window: exit
                if (event.type == sf::Event::Closed)
                    m_window.close();
            }

            sf::Vector2i cursorPosition = sf::Mouse::getPosition(m_window);
            sf::Vector2f ConvertedPosition1 = m_window.mapPixelToCoords(cursorPosition, m_gameview.GetView());
            sf::Vector2f ConvertedPosition2 = m_window.mapPixelToCoords(cursorPosition);

            m_window.clear();

            this->m_cursor.setPosition(ConvertedPosition2);

            this->m_playergun.Update(m_dt, m_player.GetPosition(), ConvertedPosition1, m_spawner);

            this->m_player.Update(m_dt, m_window);

            this->m_inventory.Update(m_cursor.getPosition());
            this->m_gameview.Update(m_dt);
            this->m_spawner.Update(m_dt, m_player.GetPosition());

            this->m_enemymanager.Update(this->m_dt, this->m_player.GetPosition(), this->m_player.GetHitBox());

            this->m_gameview.setViewCenter(m_player.GetPosition());
            this->m_window.setView(m_gameview.GetView());


            this->m_map.Draw(m_window, m_gameview);
            this->m_spawner.Draw(m_window);
            this->m_player.Draw(m_window);
            this->m_playergun.Draw(m_window);
            this->m_enemymanager.Draw(m_window);


            this->m_window.setView(m_inventory.p_view);
            this->m_window.draw(m_cursor);
            this->m_inventory.Draw(m_window);


            m_window.display();
        }

        return EXIT_SUCCESS;
    }


private:
    sf::RenderWindow m_window;

    std::string m_tilesheet;
    sf::Vector2u m_tilesize;

    MapGenerator m_map;
    Viewer m_gameview;
    Inventory m_inventory; 

    Player m_player; 
    Gun m_playergun; 

    // test1 bei einem Spawner 
    EnemieManager m_enemymanager; 
    Spawner       m_spawner; 

    TextureHolder m_textures;

    sf::Texture m_curor_texture; 
    sf::Sprite m_cursor; 

    float m_dt;
};

