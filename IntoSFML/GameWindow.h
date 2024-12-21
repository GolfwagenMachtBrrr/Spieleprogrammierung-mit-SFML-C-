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
#include "Spawner.h"
#include "MapManager.h"
#include "CollisionManager.h"

#include "HUD.h"


#include <iostream>
#include <random>


class GameWindow
{
public:

    GameWindow()
    {}

    void Start()
    {
        //Creating the Textures
        InitTextures();

        //Creating the Sounds
        InitSounds(); 
        m_gamesoundtrack.setBuffer(m_sounds.Get(Sounds::ID::SoundtrackGame)); 
        m_gamesoundtrack.setLoop(true); 
        m_gamesoundtrack.play();

        // Creating the Window
        m_window.create(sf::VideoMode(1920, 1080), "GameWindow");
        m_window.setMouseCursorVisible(false);

        //Creating the Map
        tilesize.x = 16; 
        tilesize.y = 16;
        m_gameManager.Initialize(m_textures, tilesize);

        // Creating the GameHUD
        m_gameHUD.Initalize(m_textures, m_window.getSize().x, m_window.getSize().y);

        GameLoop();
    }

    void InitTextures()
    {
        //std::string SYSTEMPATH = "C:/Users/JanSa/source/repos/tmpGameRepo/";
        std::string SYSTEMPATH = "C:/Users/JanSa/OneDrive/Desktop/Programmieren/Projekte/ProcMapGen/ProcGen/"; 
        m_textures.Load(Textures::ID::Spawner,     SYSTEMPATH + "Assets/AssetPack/Pixel Art Top Down - Basic/Texture/Statue.png");
        m_textures.Load(Textures::ID::Cursor,      SYSTEMPATH + "Assets/AssetPack/Tiny Swords/Tiny Swords (Update 010)/UI/Pointers/01.png"); 
        m_textures.Load(Textures::ID::Skeleton,    SYSTEMPATH + "Assets/Player/Textures/skeletonsprite.png");
        m_textures.Load(Textures::ID::Grass,       SYSTEMPATH + "Assets/AssetPack/Pixel Art Top Down - Basic/Texture/TX Tileset Grass.png");
        m_textures.Load(Textures::ID::Zombie,      SYSTEMPATH + "Assets/Enemy/Textures/zombie_n_skeleton2.png");
        m_textures.Load(Textures::ID::Undefined,   SYSTEMPATH + "Assets/AssetPack/Tiny Swords/Tiny Swords (Update 010)/UI/Icons/Disable_01.png");
        m_textures.Load(Textures::ID::Sword,       SYSTEMPATH + "Assets/AssetPack/Tiny Swords/Tiny Swords (Update 010)/Sword.png");
        m_textures.Load(Textures::ID::Wand,        SYSTEMPATH + "Assets/AssetPack/Tiny Swords/Tiny Swords (Update 010)/Wand.png");
        m_textures.Load(Textures::ID::House,       SYSTEMPATH + "Assets/AssetPack/Tiny Swords/Tiny Swords (Update 010)/Factions/Knights/Buildings/House/House_Blue.png");
        m_textures.Load(Textures::ID::BloodScreen, SYSTEMPATH + "Assets/Player/Textures/player_received_damage.png"); 
         
    }

    void InitSounds()
    {
        //std::string SYSTEMPATH = "C:/Users/JanSa/source/repos/tmpGameRepo/";
        std::string SYSTEMPATH = "C:/Users/JanSa/OneDrive/Desktop/Programmieren/Projekte/ProcMapGen/ProcGen/";
        m_sounds.Load(Sounds::ID::SoundtrackGame,  SYSTEMPATH + "Assets/Music & Sounds/Soundtrack/SoundTrackGame.mp3");
        m_sounds.Load(Sounds::ID::SoundtrackMenue, SYSTEMPATH + "Assets/Music & Sounds/Soundtrack/SoundTrackMenue.wav");
        m_sounds.Load(Sounds::ID::SoundZombie,     SYSTEMPATH + "Assets/Music & Sounds/Sounds/zombie.wav");
        m_sounds.Load(Sounds::ID::SoundGun,        SYSTEMPATH + "Assets/Music & Sounds/Sounds/gun.flac");
    }                                              

    
    int GameLoop()
    {
     

        while (m_window.isOpen())
        {
            // Process events
            sf::Event event;
            while (m_window.pollEvent(event))
            {
                // Close window: exit
                if (event.type == sf::Event::Closed)
                    m_window.close();
            }

            sf::Vector2i cursorPosition = sf::Mouse::getPosition(m_window);
            sf::Vector2f ConvertedPosition1 = m_window.mapPixelToCoords(cursorPosition, m_gameManager.p_view);
            sf::Vector2f ConvertedPosition2 = m_window.mapPixelToCoords(cursorPosition);

            m_window.clear();

            // Updates
            m_gameManager.Update(ConvertedPosition1, m_textures);
            m_gameHUD.Update(ConvertedPosition2, m_gameManager.p_player);

            // Draws
            m_gameManager.Draw(m_window);
            m_gameHUD.Draw(m_window);

            m_window.display();
        }

        return EXIT_SUCCESS;
    }


private:
    sf::RenderWindow m_window;

    //Ressources
    TextureHolder    m_textures;
    SoundHolder      m_sounds;

    // Gameclasses 
    MapManager       m_gameManager; 
    HUD              m_gameHUD;

    //Info
    sf::Vector2u tilesize;

    //Musik
    sf::Sound m_gamesoundtrack; 
};  

