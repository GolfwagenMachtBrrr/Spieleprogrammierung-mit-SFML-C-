#pragma once
#include "MapManager.h"
#include "Common.h"
#include "nRessources.h"

#include "HUD.h"



class GameWindow
{
public:

    GameWindow()
    {}

    void Start()
    {

        //std::string SYSTEMPATH = "C:/Users/JanSa/source/repos/tmpGameRepo/";
        std::string SYSTEMPATH = "C:/Users/JanSa/OneDrive/Desktop/Programmieren/Projekte/ProcMapGen/ProcGen/";

        // Creating Fonts
        InitFonts(SYSTEMPATH);

        //Creating the Textures
        InitTextures(SYSTEMPATH);

        //Creating the Sounds
        InitSounds(SYSTEMPATH);
        m_gamesoundtrack.setBuffer(Sounds::_SoundHolder.Get(Sounds::ID::SoundtrackGame));
        m_gamesoundtrack.setVolume(20);
        m_gamesoundtrack.setLoop(true);
        m_gamesoundtrack.play();


        // Creating the Window
        m_window.create(sf::VideoMode(1920, 1080), "GameWindow");
        m_window.setMouseCursorVisible(false);

        //Creating the Map
        m_gameManager.Initialize();

        // Creating the GameHUD
        m_gameHUD.Initalize(m_window.getSize().x, m_window.getSize().y);
        

        GameLoop();
    }

    void InitTextures(const std::string& SYSTEMPATH)
    {
        Textures::_TextureHolder.Load(Textures::ID::Spawner,     SYSTEMPATH + "Assets/AssetPack/Pixel Art Top Down - Basic/Texture/Statue.png");
        Textures::_TextureHolder.Load(Textures::ID::Cursor,      SYSTEMPATH + "Assets/AssetPack/Tiny Swords/Tiny Swords (Update 010)/UI/Pointers/01.png");
        Textures::_TextureHolder.Load(Textures::ID::Player,      SYSTEMPATH + "Assets/Player/Textures/skeletonsprite.png");
        Textures::_TextureHolder.Load(Textures::ID::Grass,       SYSTEMPATH + "Assets/AssetPack/Pixel Art Top Down - Basic/Texture/TX Tileset Grass.png");
        Textures::_TextureHolder.Load(Textures::ID::Zombie,      SYSTEMPATH + "Assets/Enemy/Textures/zombie_n_skeleton2.png");
        Textures::_TextureHolder.Load(Textures::ID::Undefined,   SYSTEMPATH + "Assets/AssetPack/Tiny Swords/Tiny Swords (Update 010)/UI/Icons/Disable_01.png");
        Textures::_TextureHolder.Load(Textures::ID::Sword,       SYSTEMPATH + "Assets/AssetPack/Tiny Swords/Tiny Swords (Update 010)/Sword.png");
        Textures::_TextureHolder.Load(Textures::ID::Wand,        SYSTEMPATH + "Assets/AssetPack/Tiny Swords/Tiny Swords (Update 010)/Wand.png");
        Textures::_TextureHolder.Load(Textures::ID::Wand_bullet, SYSTEMPATH + "Assets/Origin/lpc_entry/lpc_entry/png/bow/arrow.png");
        Textures::_TextureHolder.Load(Textures::ID::House,       SYSTEMPATH + "Assets/AssetPack/Tiny Swords/Tiny Swords (Update 010)/Factions/Knights/Buildings/House/House_Blue.png");
        Textures::_TextureHolder.Load(Textures::ID::BloodScreen, SYSTEMPATH + "Assets/Effects/player_received_damage.png");
        Textures::_TextureHolder.Load(Textures::ID::DeathScreen, SYSTEMPATH + "Assets/Effects/OhNoImDEAD.png");
    }

    void InitSounds(const std::string& SYSTEMPATH)
    {
        Sounds::_SoundHolder.Load(Sounds::ID::SoundtrackGame,    SYSTEMPATH + "Assets/Music & Sounds/Soundtrack/SoundTrackGame.mp3");
        Sounds::_SoundHolder.Load(Sounds::ID::SoundtrackMenue,   SYSTEMPATH + "Assets/Music & Sounds/Soundtrack/SoundTrackMenue.wav");
        Sounds::_SoundHolder.Load(Sounds::ID::SoundZombie,       SYSTEMPATH + "Assets/Music & Sounds/Sounds/zombie.wav");
        Sounds::_SoundHolder.Load(Sounds::ID::SoundGun,          SYSTEMPATH + "Assets/Music & Sounds/Sounds/gun.flac");
        Sounds::_SoundHolder.Load(Sounds::ID::SoundPlayerDeath,  SYSTEMPATH + "Assets/Music & Sounds/Sounds/PlayerDeath/PlayerDeath.mp3");
    }     


    void InitFonts(const std::string& SYSTEMPATH)
    {
        Fonts::_FontHolder.Load(Fonts::ID::OnlyFont,             SYSTEMPATH + "Assets/Fonts/NotoSansThai-Regular.ttf");
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
            sf::Vector2f mpos1 = m_window.mapPixelToCoords(cursorPosition, GameData::Views::_HUDView);
            sf::Vector2f mpos2 = m_window.mapPixelToCoords(cursorPosition);


            GameData::Views::_GameMousePosition = mpos1;
            GameData::Views::_HUDMousePosition = mpos2; 

            m_window.clear();

            // Updates
            m_gameManager.Update();
            m_gameHUD.Update();

            // Draws
            m_gameManager.Draw(m_window);
            m_gameHUD.Draw(m_window);

            m_window.display();
        }

        return EXIT_SUCCESS;
    }


private:
    sf::RenderWindow m_window;

    // Gameclasses 
    MapMaker       m_gameManager; 
    HUD              m_gameHUD;

    //Musik
    sf::Sound m_gamesoundtrack; 
};  

