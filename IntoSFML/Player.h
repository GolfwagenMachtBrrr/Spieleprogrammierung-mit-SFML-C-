#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <iostream>
#include <vector>

#include "ResourceHolder.h"
#include "CollisionManager.h"

#include "GameObject.h"
#include "TimeObject.h"
#include "Entity.h"

#include "Gun.h"



#define SPRITEUNIT 64
#define FORWARD 0
#define BACKWARD 2
#define RIGHTWARD 3
#define LEFTWARD 1
#define MOVEMENT 5
#define SECOND 5


class Player : public TimeObject, public GameObject, public Entity 
{
public: 
	Player() {}

	void Initalize(const TextureHolder& textures)
	{
		// Initalizing player stats
		m_speed = 0.125; 
		m_health = 100; 

		m_sprite.setTexture(textures.Get(Textures::ID::Skeleton));
		m_sprite.setTextureRect(sf::IntRect(0, 0, 64, 64));
		m_sprite.setPosition(450, 300);

		// Weapons: 
		// TODO - Überarbeitung: 
		m_gun = new Gun(); 
	}

	void Update(const float& dt, const sf::Vector2f convertedmouseposition, CollisionManager* collisonmanager, const TextureHolder& textures)
	{
		MovePlayer(dt);
		if (m_health < 0) {
			std::cout << "Huh Dead! " << std::endl; 
		}

		//Weapons: 
		m_gun->Update(dt, m_position, convertedmouseposition, textures, collisonmanager); 

	}

	void Draw(sf::RenderWindow& window)
	{
		window.draw(m_sprite);

		//weapons
		m_gun->Draw(window); 
	}

	void OnCollision(GameObject& other) override
	{

		switch (other.objectType)
		{
		case Textures::ID::House:
			std::cout << "Dammit, it collides" << std::endl;
			HandleCollision(other.GetPosition(), 1);
			break;
		case Textures::ID::Spawner:
			HandleCollision(other.GetPosition(), 5);
			break;
		case Textures::ID::Zombie:
			std::cout << "Dammit, it collides" << std::endl; 
			if (lastEnemyID != other.u_objectID) {
				m_health -= 10;
				lastEnemyID = other.u_objectID;
				p_onhit = true; 
			}
			break; 
		}
	}

	bool ValidateRendering(const sf::Sprite& otherobj) const
	{
		// O...Object, P...Player, D...Difference
		int xO = otherobj.getPosition().x / GameData::data_tilesize.x, yO = otherobj.getPosition().y / GameData::data_tilesize.y;
		int xP = m_position.x / GameData::data_tilesize.x, yP = m_position.y / GameData::data_tilesize.y;
		int xD = std::abs(xP - xO), yD = std::abs(yP - yO);

		return (xD < GameData::data_renderrange && yD < GameData::data_renderrange);
	}

	void SetKillcount(int x)
	{
		m_killcount = x; 
	}

	int  GetKillcount() const
	{
		return m_killcount; 
	}

	void SetHealth(int x);
	int GetHealth() const
	{
		return m_health; 
	}

private:
	void MovePlayer(const float& dt)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
			sf::Vector2f newposition = m_position + sf::Vector2f(0, -1) * m_speed * dt;

			m_sprite.setPosition(newposition);
			m_sprite.setTextureRect(sf::IntRect((movementIndicator / MOVEMENT) * SPRITEUNIT, FORWARD, SPRITEUNIT, SPRITEUNIT));
			movementIndicator++;
			if (movementIndicator / MOVEMENT == 9) {
				movementIndicator = 0;
			}

		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
			sf::Vector2f newposition = m_position + sf::Vector2f(0, 1) * m_speed * dt;

			m_sprite.setPosition(newposition);
			m_sprite.setTextureRect(sf::IntRect((movementIndicator / MOVEMENT) * SPRITEUNIT, BACKWARD * SPRITEUNIT, SPRITEUNIT, SPRITEUNIT));
			movementIndicator++;
			if (movementIndicator / MOVEMENT == 9) {
				movementIndicator = 0;
			}

		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			sf::Vector2f newposition = m_position + sf::Vector2f(1, 0) * m_speed * dt;


			m_sprite.setPosition(m_position + sf::Vector2f(1, 0) * m_speed * dt);
			m_sprite.setTextureRect(sf::IntRect((movementIndicator / MOVEMENT) * SPRITEUNIT, RIGHTWARD * SPRITEUNIT, SPRITEUNIT, SPRITEUNIT));
			movementIndicator++;
			if (movementIndicator / MOVEMENT == 9) {
				movementIndicator = 0;
			}


		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
			sf::Vector2f newposition = m_position + sf::Vector2f(-1, 0) * m_speed * dt;


			m_sprite.setPosition(m_position + sf::Vector2f(-1, 0) * m_speed * dt);
			m_sprite.setTextureRect(sf::IntRect((movementIndicator / MOVEMENT) * SPRITEUNIT, LEFTWARD * SPRITEUNIT, SPRITEUNIT, SPRITEUNIT));
			movementIndicator++;
			if (movementIndicator / MOVEMENT == 9) {
				movementIndicator = 0;
			}

		}

		m_position = m_sprite.getPosition();
	}

public: 
	Gun* m_gun;
	bool p_onhit = false; 

private:
 


private: 
	// until its fixed
	int movementIndicator = 0;
	int lastEnemyID = -42;
	int m_killcount = 0; 
};
