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
#include "ResourceHolder.h"
#include "Inventory.h"
#include "EnemyManager.h"
#include "Spawner.h"
#include "MapManager.h"
#include "CollisionManager.h"


#include <iostream>
#include <random>


class GameWindow
{
public:

    GameWindow()
    {}

    void Start(bool start)
    {
        if (start)
        {
            this->InitTextures(); 
            this->InitWindow();
            this->InitPlayer(); 
            this->IntitOtherValues();
            this->InitMap();
            this->InitViewer();
            this->GameLoop();
        }
    }

    void InitTextures()
    {
        //std::string SYSTEMPATH = "C:/Users/JanSa/source/repos/tmpGameRepo/";
        std::string SYSTEMPATH = "C:/Users/JanSa/OneDrive/Desktop/Programmieren/Projekte/ProcMapGen/ProcGen/"; 
        m_textures.Load(Textures::ID::Spawner,   SYSTEMPATH + "Assets/AssetPack/Pixel Art Top Down - Basic/Texture/Statue.png");
        m_textures.Load(Textures::ID::Cursor,    SYSTEMPATH + "Assets/AssetPack/Tiny Swords/Tiny Swords (Update 010)/UI/Pointers/01.png"); 
        m_textures.Load(Textures::ID::Skeleton,  SYSTEMPATH + "Assets/Player/Textures/skeletonsprite.png");
        m_textures.Load(Textures::ID::Grass,     SYSTEMPATH + "Assets/AssetPack/Pixel Art Top Down - Basic/Texture/TX Tileset Grass.png");
        m_textures.Load(Textures::ID::Zombie,    SYSTEMPATH + "Assets/Enemy/Textures/zombie_n_skeleton2.png");
        m_textures.Load(Textures::ID::Undefined, SYSTEMPATH + "Assets/AssetPack/Tiny Swords/Tiny Swords (Update 010)/UI/Icons/Disable_01.png");
        m_textures.Load(Textures::ID::Sword,     SYSTEMPATH + "Assets/AssetPack/Tiny Swords/Tiny Swords (Update 010)/Sword.png");
        m_textures.Load(Textures::ID::Wand,      SYSTEMPATH + "Assets/AssetPack/Tiny Swords/Tiny Swords (Update 010)/Wand.png");
        m_textures.Load(Textures::ID::House,     SYSTEMPATH + "Assets/AssetPack/Tiny Swords/Tiny Swords (Update 010)/Factions/Knights/Buildings/House/House_Blue.png");
         
    }

    void IntitOtherValues()
    {
        this->m_tilesheet = "../Assets/World/NumsVer3.png";
        this->m_tilesize.x = 16;
        this->m_tilesize.y = 16;

        this->m_cursor.setTexture(m_textures.Get(Textures::ID::Cursor));
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

        this->m_map.Initialize(m_tilesize, m_textures, width, height);
        this->m_map.Generate();
        this->m_mapM.Initialize(m_textures, m_map, m_collisionmanager); 
        
    }

    void InitViewer()
    {
        sf::Vector2f startingPosition(0, 0);
        float speed = 100;
        float zoom = 1;

        this->m_gameview.Initialize(startingPosition, speed, zoom);
    }

    void InitPlayer()
    {
        this->m_player.Initalize(m_textures);
    }
    
    int GameLoop()
    {
        sf::Clock time; 
        while (m_window.isOpen())
        {
            // Calculate DeltaTime
            m_dt = time.getElapsedTime().asMilliseconds(); 
            if (m_dt != 0) {
                time.restart();
            }
             

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

            // Updates
            this->m_player.Update(m_dt, m_window, m_map);
            this->m_mapM.Update(m_dt, m_player, m_map);
            this->m_playergun.Update(m_dt, m_player.GetPosition(), ConvertedPosition1, m_mapM, m_collisionmanager);
            this->m_inventory.Update(m_cursor.getPosition());
            this->m_gameview.Update(m_dt);
            this->m_collisionmanager.checkCollisions(); 
          

            this->m_gameview.setViewCenter(m_player.GetPosition());
            this->m_window.setView(m_gameview.GetView());

            // Draws
            this->m_map.Draw(m_window, m_gameview);
            this->m_mapM.Draw(m_window);
            this->m_player.Draw(m_window);
            this->m_playergun.Draw(m_window);

            // Changing Views
            this->m_window.setView(m_inventory.p_view);
            this->m_window.draw(m_cursor);
            this->m_inventory.Draw(m_window);


            m_window.display();

            sf::sleep(sf::microseconds(1));
        }

        return EXIT_SUCCESS;
    }


private:
    sf::RenderWindow m_window;
    std::string      m_tilesheet;
    sf::Vector2u     m_tilesize;

    TextureHolder    m_textures;
    CollisionManager m_collisionmanager; 
    MapGenerator     m_map;
    MapManager       m_mapM; 

    Viewer m_gameview;
    Inventory m_inventory; 

    Player m_player; 
    Gun m_playergun; 

   

    sf::Sprite m_cursor; 
    float m_dt;
};

