#include "Player.h"
#include <iostream>

#define SPRITEUNIT 64
#define FORWARD 0
#define BACKWARD 2
#define RIGHTWARD 3
#define LEFTWARD 1
#define MOVEMENT 5
#define SECOND 5


void Player::Initalize(TextureHolder& textureholder)
{
	m_texture = textureholder.GetTexture("skeleton"); 
	m_sprite.setTexture(m_texture);
	m_sprite.setTextureRect(sf::IntRect(0, 0, 64, 64));
	m_sprite.setPosition(450, 300);
}

void Player::Update(const float& dt, sf::RenderWindow& window)
{
	MovePlayer(dt);
}

void Player::Draw(sf::RenderWindow& window)
{
	window.draw(m_sprite); 
}

void Player::MovePlayer(const float &dt)
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
