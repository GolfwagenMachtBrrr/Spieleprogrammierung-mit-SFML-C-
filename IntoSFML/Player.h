#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "Bullet.h"
#include "ResourceHolder.h"
#include <vector>

#define SPRITEUNIT 64
#define FORWARD 0
#define BACKWARD 2
#define RIGHTWARD 3
#define LEFTWARD 1
#define MOVEMENT 5
#define SECOND 5


class Player
{
public: 

	Player() 
		: m_speed(0.125/10), p_health(100)
	{}

	void Initalize(TextureHolder& textures)
	{
		m_sprite.setTexture(textures.Get(Textures::ID::Skeleton));
		m_sprite.setTextureRect(sf::IntRect(0, 0, 64, 64));
		m_sprite.setPosition(450, 300);

		p_hitbox.setSize(sf::Vector2f(64, 64));
		p_hitbox.setOutlineColor(sf::Color::Red);
		p_hitbox.setOutlineThickness(1);
		p_hitbox.setFillColor(sf::Color::Transparent);
	}

	void Update(const float& dt, sf::RenderWindow& window)
	{
		MovePlayer(dt);
		p_hitbox.setPosition(m_position);
	}

	void Draw(sf::RenderWindow& window)
	{
		window.draw(p_hitbox);
		window.draw(m_sprite);
	}

	sf::Vector2f GetPosition()
	{
		return this->m_position; 
	}


private: 
	void MovePlayer(const float& dt)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
			m_sprite.setPosition(m_position + sf::Vector2f(0, -1) * m_speed * dt);
			m_sprite.setTextureRect(sf::IntRect((movementIndicator / MOVEMENT) * SPRITEUNIT, FORWARD, SPRITEUNIT, SPRITEUNIT));
			movementIndicator++;
			if (movementIndicator / MOVEMENT == 9) {
				movementIndicator = 0;
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
			m_sprite.setPosition(m_position + sf::Vector2f(0, 1) * m_speed * dt);
			m_sprite.setTextureRect(sf::IntRect((movementIndicator / MOVEMENT) * SPRITEUNIT, BACKWARD * SPRITEUNIT, SPRITEUNIT, SPRITEUNIT));
			movementIndicator++;
			if (movementIndicator / MOVEMENT == 9) {
				movementIndicator = 0;
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			m_sprite.setPosition(m_position + sf::Vector2f(1, 0) * m_speed * dt);
			m_sprite.setTextureRect(sf::IntRect((movementIndicator / MOVEMENT) * SPRITEUNIT, RIGHTWARD * SPRITEUNIT, SPRITEUNIT, SPRITEUNIT));
			movementIndicator++;
			if (movementIndicator / MOVEMENT == 9) {
				movementIndicator = 0;
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
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
	sf::RectangleShape p_hitbox;
	int				   p_health;
private: 

	sf::Sprite		   m_sprite; 

	sf::Vector2f	   m_position;
	float			   m_speed; 

	// until its fixed
	int movementIndicator = 0; 
};

