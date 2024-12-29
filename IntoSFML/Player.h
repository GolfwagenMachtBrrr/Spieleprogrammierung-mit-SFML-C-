#pragma once
#include "Common.h"
#define SPRITEUNIT 64
#define FORWARD 0
#define BACKWARD 2
#define RIGHTWARD 3
#define LEFTWARD 1
#define MOVEMENT 100
#define SECOND 5

#include "nGameData.h"




class Player : public GameObject, public Entity 
{
public: 
	Player(const Textures::ID tID, const Fonts::ID fID, const sf::Vector2f& InitalPosition, const sf::IntRect& TextureRect)
		: GameObject(tID, fID, InitalPosition, TextureRect)
	{
		SetupEntity("username", 100, NULL, 0.125, NULL);
	}

	void Update() override
	{
		MovePlayer();
	}
	void Draw(sf::RenderWindow& window) const noexcept override
	{
		window.draw(m_sprite);
	}
	void OnCollision(GameObject& other)
	{

		switch (other.GetObjectTextureID())
		{
		case Textures::ID::House:
			HandleCollision(other.GetPosition(), 1);
			break;
		case Textures::ID::Spawner:
			HandleCollision(other.GetPosition(), 5);
			break;
		case Textures::ID::Zombie:
			if (other.enabled)
			{
				m_health -= 10;
				other.enabled = false;
			}
			break;
		}

	}

private:
	void MovePlayer()
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
			sf::Vector2f newposition = m_position + sf::Vector2f(0, -1) * m_speed * GameData::_DeltaTime;

			m_sprite.setPosition(newposition);
			m_sprite.setTextureRect(sf::IntRect((movementIndicator / MOVEMENT) * SPRITEUNIT, FORWARD, SPRITEUNIT, SPRITEUNIT));
			movementIndicator++;
			if (movementIndicator / MOVEMENT == movgoal) {
				movementIndicator = 0;
			}

		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
			sf::Vector2f newposition = m_position + sf::Vector2f(0, 1) * m_speed * GameData::_DeltaTime;

			m_sprite.setPosition(newposition);
			m_sprite.setTextureRect(sf::IntRect((movementIndicator / MOVEMENT) * SPRITEUNIT, BACKWARD * SPRITEUNIT, SPRITEUNIT, SPRITEUNIT));
			movementIndicator++;
			if (movementIndicator / MOVEMENT == movgoal) {
				movementIndicator = 0;
			}

		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			sf::Vector2f newposition = m_position + sf::Vector2f(1, 0) * m_speed * GameData::_DeltaTime;


			m_sprite.setPosition(m_position + sf::Vector2f(1, 0) * m_speed * GameData::_DeltaTime);
			m_sprite.setTextureRect(sf::IntRect((movementIndicator / MOVEMENT) * SPRITEUNIT, RIGHTWARD * SPRITEUNIT, SPRITEUNIT, SPRITEUNIT));
			movementIndicator++;
			if (movementIndicator / MOVEMENT == movgoal) {
				movementIndicator = 0;
			}


		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
			sf::Vector2f newposition = m_position + sf::Vector2f(-1, 0) * m_speed * GameData::_DeltaTime;


			m_sprite.setPosition(m_position + sf::Vector2f(-1, 0) * m_speed * GameData::_DeltaTime);
			m_sprite.setTextureRect(sf::IntRect((movementIndicator / MOVEMENT) * SPRITEUNIT, LEFTWARD * SPRITEUNIT, SPRITEUNIT, SPRITEUNIT));
			movementIndicator++;
			if (movementIndicator / MOVEMENT == movgoal) {
				movementIndicator = 0;
			}

		}

		m_position = m_sprite.getPosition();
		GameData::Player::_PlayerPosition = m_position;
	}

	int movementIndicator = 0;
	int movgoal = 9; 
};
