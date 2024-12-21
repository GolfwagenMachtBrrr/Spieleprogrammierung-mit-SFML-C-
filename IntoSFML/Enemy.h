#pragma once
#include "SFML/Graphics.hpp"
#include "WayPoint.h"
#include "ResourceHolder.h"
#include "Player.h"
#include "MapGenerator.h"
#include "game_algorithm.h"
#include "GameObject.h"
#include "Entity.h"

#include <string>
#include <iostream>

#define SPRITEUNIT 32
#define MOVEMENT 1

#define FORWARD 7
#define LEFTWARD 3
#define BACKWARD 1
#define RIGHTWARD 5

typedef ResourceHolder<sf::Texture, Textures::ID> TextureHolder;

class Enemy : public GameObject, public Entity
{
public:

	Enemy() {}

	void LoadAssets(const sf::Vector2f &startingPos)
	{
		this->m_sprite.setTextureRect(sf::IntRect(32*0, 32*1, 32, 32));
		this->m_sprite.setPosition(startingPos);

		this->m_font.loadFromFile("C:/Users/JanSa/OneDrive/Desktop/Programmieren/Projekte/ProcMapGen/ProcGen/Assets/Fonts/NotoSansThai-Regular.ttf");
		this->m_text.setFont(m_font); 
		this->m_text.setCharacterSize(10); 
		
		// Fürs debuggen bleibt die Hitbox
		p_hitbox.setSize(sf::Vector2f(32, 32)); 
		p_hitbox.setPosition(startingPos); 
		p_hitbox.setOutlineColor(sf::Color::Red);
		p_hitbox.setOutlineThickness(1);
		p_hitbox.setFillColor(sf::Color::Transparent);
	}
	

	void Initialize(const TextureHolder &texures, Textures::ID ID, const sf::Vector2f& position)
	{
		LoadAssets(position);

		m_position = position;
		objectType = ID;

		m_sprite.setTexture(texures.Get(ID));

		m_speed = 0.125/3;
		m_damage = 10;
		m_attackspeed = 500;
	}

	void Update(const float& dt, Player* player)
	{
		if (!m_health) {
			p_isActive = false; 
			return; 
		}
		m_text.setString(std::to_string(m_health));
		m_text.setPosition(m_position); 

		p_hitbox.setPosition(m_position); 

		this->Move(dt, player->GetPosition());

	}

	void Draw(sf::RenderWindow& window, Player* player) const
	{
		if(player->ValidateRendering(m_position))
		{
			window.draw(m_sprite);
			window.draw(p_hitbox);
			window.draw(m_text);
		}

	} 

public:
	// Getter Functions
	sf::Vector2f GetPosition() const override
	{
		return m_position; 
	}

	sf::FloatRect GetBoundingBox() const override
	{
		return m_sprite.getGlobalBounds();
	}

	void OnCollision(GameObject& other) override
	{

		switch (other.objectType)
		{
		case Textures::ID::Zombie:
			HandleCollision(other.GetPosition(), 20);
			break; 
		case Textures::ID::House:
			HandleCollision(other.GetPosition(), 5);
			break; 
		case Textures::ID::Spawner:
			HandleCollision(other.GetPosition(), 5);
			break;

		case Textures::ID::Wand_bullet:
			if (LastBulletID != other.u_objectID) {
				m_health -= 10;
				LastBulletID = other.u_objectID;
			}
			break; 
		}
		
	}

	//quickfix
private: 
	int LastBulletID = -23; 

private:
	// Movement/shooting Calculations
	sf::Vector2f NormalizeVector(sf::Vector2f& input) const
	{
		float m = sqrt(input.x * input.x + input.y * input.y);
		sf::Vector2f normalizedVector;

		normalizedVector.x = input.x /= m;
		normalizedVector.y = input.y /= m;

		return normalizedVector;
	}

	sf::Vector2f GetDirectionVector() const
	{
		sf::Vector2f direction;
		direction = m_target - m_position;
		direction = NormalizeVector(direction);

		return direction;
	}

	sf::Vector2f GetDirectionVector(const sf::Vector2f& target) const
	{
		sf::Vector2f direction;
		direction = target - m_position;
		direction = NormalizeVector(direction);

		return direction;
	}

	sf::Vector2f GetClosestTarget(const sf::Vector2f& firstTarget, const sf::Vector2f& secondTarget) const
	{
		float diff_first = std::abs(firstTarget.x - this->m_position.x);
		diff_first += std::abs(firstTarget.y - this->m_position.y);

		float diff_second = std::abs(secondTarget.x - this->m_position.x);
		diff_second += std::abs(secondTarget.y - this->m_position.y);

		if (diff_first < diff_second)
		{
			return this->GetDirectionVector(firstTarget);
		}

		return this->GetDirectionVector(secondTarget);
	}

	void Move(const float& dt, const sf::Vector2f& playerPosition)
	{
		sf::Vector2f direction; direction = this->GetDirectionVector(playerPosition);
		sf::Vector2f hypotheticalPosition = m_position + direction * dt * m_speed;


		if (hypotheticalPosition.x < 0 || hypotheticalPosition.y < 0) {
			direction.x = 0; 
			direction.y = 0;
			hypotheticalPosition = m_position + direction * dt * m_speed;
		}

		if (m_oncollision) {
			direction.x *= -1; 
			direction.y *= -1; 

			for (int i = 0; i < 10; i++) {
				hypotheticalPosition = m_position + direction * dt * m_speed;
				this->m_sprite.setPosition(hypotheticalPosition);
			}
			
			m_oncollision = false; 
		}


		//AdjustTileMap(map, hypotheticalPosition); 
		this->m_sprite.setPosition(hypotheticalPosition);
		this->m_position = this->m_sprite.getPosition();

		//impl enemy animations 
	    this->WalkAnimation(direction, dt);
	}

	void WalkAnimation(const sf::Vector2f& direction, const float &deltatime)
	{	
		if (direction.x == 0 && direction.y == 0) {
			return; 
		}

		if (direction.x > 0 && direction.y < 0) {
			m_sprite.setTextureRect(sf::IntRect((u_movementindicator / MOVEMENT) * SPRITEUNIT, FORWARD*SPRITEUNIT, SPRITEUNIT, SPRITEUNIT));
			u_movementindicator++;
			if (u_movementindicator / MOVEMENT == 3) {
				u_movementindicator = 0;
			}
		}

		else if (direction.x > 0 && direction.y > 0 && direction.x < direction.y) {

			//std::cout << "Backward" << std::endl;

			m_sprite.setTextureRect(sf::IntRect((u_movementindicator / MOVEMENT) * SPRITEUNIT, BACKWARD * SPRITEUNIT, SPRITEUNIT, SPRITEUNIT));
			u_movementindicator++;
			if (u_movementindicator / MOVEMENT == 3) {
				u_movementindicator = 0;
			}
		}

		else if (direction.x < 0 && direction.y > 0) {

			//std::cout << "Leftward" << std::endl;

			m_sprite.setTextureRect(sf::IntRect((u_movementindicator / MOVEMENT) * SPRITEUNIT, LEFTWARD * SPRITEUNIT, SPRITEUNIT, SPRITEUNIT));
			u_movementindicator++;
			if (u_movementindicator / MOVEMENT == 3) {
				u_movementindicator = 0;
			}
		}

		else if (direction.x > 0 && direction.y > 0 && direction.x > direction.y) {

			//std::cout << "Rightward" << std::endl;

			m_sprite.setTextureRect(sf::IntRect((u_movementindicator/MOVEMENT) * SPRITEUNIT, RIGHTWARD * SPRITEUNIT, SPRITEUNIT, SPRITEUNIT));
			u_movementindicator++;
			if (u_movementindicator / MOVEMENT == 3) {
				u_movementindicator = 0;
			}
		}

		
	}


private:
	sf::RectangleShape p_hitbox; 

public: 
	int		p_ID = -1; 
	bool    p_isActive = true; 
	bool    m_oncollision = false;
	int     u_movementindicator = 0;

private:
	sf::Vector2f m_target;

	sf::Font m_font; 
	sf::Text m_text; 

	int m_attackspeed; 
};