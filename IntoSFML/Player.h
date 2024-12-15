#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "Bullet.h"
#include "ResourceHolder.h"
#include "Inventory.h"
#include "Item.h"
#include "MapGenerator.h"
#include "GameObject.h"
#include "Entity.h"

#include <vector>


#define SPRITEUNIT 64
#define FORWARD 0
#define BACKWARD 2
#define RIGHTWARD 3
#define LEFTWARD 1
#define MOVEMENT 5
#define SECOND 5


class Player : public GameObject
{
public: 

	Player() 
		: m_speed(0.125), p_health(100)
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

	void Update(const float& dt, sf::RenderWindow& window, MapGenerator &map)
	{
		MovePlayer(dt, map);
		p_hitbox.setPosition(m_position);
	}

	void Draw(sf::RenderWindow& window)
	{
		window.draw(m_sprite);
	}

	sf::Vector2f GetPosition()
	{
		return this->m_position; 
	}

	sf::FloatRect GetBoundingBox() const override
	{
		return p_hitbox.getGlobalBounds();
	}

	void OnCollision(GameObject& other) override
	{
		std::cout << "this is hapening" << std::endl;
		Entity* otherEntity = dynamic_cast<Entity*>(&other);

		if (otherEntity) {
			HandleEntityCollision(otherEntity);
		}

		switch (other.objectID)
		{
		case Textures::ID::House:
			std::cout << "this is hapening" << std::endl;
			HandleEntityCollision(otherEntity);
			break;
		case Textures::ID::Zombie:
			std::cout << " with a zombie" << std::endl;
			break; 
		}
	}

	void HandleEntityCollision(Entity* entity) {
		// Einfache Abstoßungslogik (basierend auf den Positionen)
		sf::Vector2f direction = m_position - entity->p_position;
		float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
		if (length > 0) {
			direction /= length; // Normalisieren
			m_sprite.setPosition(m_position + direction * 5.0f);
		}
	}

private: 
	void MovePlayer(const float& dt, MapGenerator& map)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
			sf::Vector2f newposition = m_position + sf::Vector2f(0, -1) * m_speed * dt; 

			if (true) {
				m_sprite.setPosition(newposition);
				m_sprite.setTextureRect(sf::IntRect((movementIndicator / MOVEMENT) * SPRITEUNIT, FORWARD, SPRITEUNIT, SPRITEUNIT));
				movementIndicator++;
				if (movementIndicator / MOVEMENT == 9) {
					movementIndicator = 0;
				}
			}
			
			
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
			sf::Vector2f newposition = m_position + sf::Vector2f(0, 1) * m_speed * dt;

			if (true) {
				m_sprite.setPosition(newposition);
				m_sprite.setTextureRect(sf::IntRect((movementIndicator / MOVEMENT) * SPRITEUNIT, BACKWARD * SPRITEUNIT, SPRITEUNIT, SPRITEUNIT));
				movementIndicator++;
				if (movementIndicator / MOVEMENT == 9) {
					movementIndicator = 0;
				}
			}
			
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			sf::Vector2f newposition = m_position + sf::Vector2f(1,0) * m_speed * dt;

			if (true) {
				m_sprite.setPosition(m_position + sf::Vector2f(1, 0) * m_speed * dt);
				m_sprite.setTextureRect(sf::IntRect((movementIndicator / MOVEMENT) * SPRITEUNIT, RIGHTWARD * SPRITEUNIT, SPRITEUNIT, SPRITEUNIT));
				movementIndicator++;
				if (movementIndicator / MOVEMENT == 9) {
					movementIndicator = 0;
				}
			}
			
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
			sf::Vector2f newposition = m_position + sf::Vector2f(-1, 0) * m_speed * dt;

			if (true) {
				m_sprite.setPosition(m_position + sf::Vector2f(-1, 0) * m_speed * dt);
				m_sprite.setTextureRect(sf::IntRect((movementIndicator / MOVEMENT) * SPRITEUNIT, LEFTWARD * SPRITEUNIT, SPRITEUNIT, SPRITEUNIT));
				movementIndicator++;
				if (movementIndicator / MOVEMENT == 9) {
					movementIndicator = 0;
				}
			}
			
		}

		m_position = m_sprite.getPosition();
	}

	bool YouShallPass(const sf::Vector2f& reisepass, MapGenerator &map) {
		float x = reisepass.x / map.GetTileSize().x, y = reisepass.y / map.GetTileSize().y;
		if (map.p_tileMap[x][y].occupied == false || IsEnemy(map, x,y)) {
			return true; 
		}
		return false; 
	}

	bool IsEnemy(MapGenerator& map, int x, int y) {
		Textures::ID type = map.p_tileMap[x][y].occupationID; 
		switch (type)
		{
		case Textures::ID::Zombie:
			return true; 
		}
		
		return false; 
	}

	void PickUpItem(Inventory &inventory, Item &item)
	{
		inventory.AddItem(item.id); 
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
