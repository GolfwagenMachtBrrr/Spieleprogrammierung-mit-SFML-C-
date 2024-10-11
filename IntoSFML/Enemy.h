#pragma once
#include "SFML/Graphics.hpp"
#include "WayPoint.h"
#include "TextureHolder.h"
#include <string>

#include <iostream>

#define SPRITEUNIT 32
#define MOVEMENT 5

#define FORWARD 0
#define LEFTWARD 1
#define BACKWARD 2
#define RIGHTWARD 3



class Enemy
{
public:
	void LoadAssets(const sf::Vector2f &startingPos, TextureHolder &textureholder)
	{
		this->m_bodytexture.loadFromFile("C:/Users/JanSa/OneDrive/Desktop/Programmieren/Projekte/ProcMapGen/ProcGen/Assets/Enemy/Textures/zombiesprite.png");
		//m_bodytexture = textureholder.GetTexture("zombie");

		this->m_bodysprite.setTexture(m_bodytexture);
		this->m_bodysprite.setTextureRect(sf::IntRect(32, 32, 32, 32));
		this->m_bodysprite.setPosition(startingPos);

	}
	
	void Initialize(const float& speed, const int& damage, const __int32& attackspeed, const WayPoint& waypoint, const sf::Color& color, TextureHolder &textureholder)
	{
		LoadAssets(waypoint.position, textureholder);

		this->m_speed = speed;
		this->m_damage = damage;
		this->m_attackspeed = attackspeed;
		this->m_target = waypoint.target;
		this->m_position = waypoint.position; 

	}


	int Update(const float& dt, const sf::Vector2f& playerPosition)
	{
		this->Move(dt, playerPosition);
		if (this->AttackTimeoutPassed())
		{
			//return this->DamageDealtToEnemy(playerHitbox);
		}
		return 0;
	}

	int Update(const float& dt)
	{
		this->Move(dt);
		return 0;
	}

	void Draw(sf::RenderWindow& window) const
	{
		window.draw(m_bodysprite);
	}

public:
	// Getter Functions
	sf::Vector2f GetPosition() const
	{
		return this->m_position; 
	}

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

	void WalkAnimation(const sf::Vector2f& direction, const float &deltatime)
	{
		sf::Vector2f newPosition = m_position + direction * deltatime * m_speed; 

		if (direction.x == 0 && direction.y < 0) {
		
			m_bodysprite.setTextureRect(sf::IntRect((u_movementindicator / MOVEMENT) * SPRITEUNIT, FORWARD, SPRITEUNIT, SPRITEUNIT));
			u_movementindicator++;
			if (u_movementindicator / MOVEMENT == 9) {
				u_movementindicator = 0;
			}
		}

		if (direction.x == 0 && direction.y > 0) {

			m_bodysprite.setTextureRect(sf::IntRect((u_movementindicator / MOVEMENT) * SPRITEUNIT, BACKWARD, SPRITEUNIT, SPRITEUNIT));
			u_movementindicator++;
			if (u_movementindicator / MOVEMENT == 9) {
				u_movementindicator = 0;
			}
		}

		if (direction.x < 0 && direction.y == 0) {
			m_bodysprite.setTextureRect(sf::IntRect((u_movementindicator / MOVEMENT) * SPRITEUNIT, LEFTWARD, SPRITEUNIT, SPRITEUNIT));
			u_movementindicator++;
			if (u_movementindicator / MOVEMENT == 9) {
				u_movementindicator = 0;
			}
		}

		if (direction.x > 0 && direction.y == 0) {

			m_bodysprite.setTextureRect(sf::IntRect((u_movementindicator / MOVEMENT) * SPRITEUNIT, RIGHTWARD, SPRITEUNIT, SPRITEUNIT));
			u_movementindicator++;
			if (u_movementindicator / MOVEMENT == 9) {
				u_movementindicator = 0;
			}
		}

		
	}

	void Move(const float& dt, const sf::Vector2f& playerPosition)
	{
		sf::Vector2f direction; direction = this->GetDirectionVector(playerPosition);
		this->m_bodysprite.setPosition(this->m_position + direction * this->m_speed * dt);
		this->m_position = this->m_bodysprite.getPosition();

		//impl enemy animations 
		this->WalkAnimation(direction, dt);
	}

	void Move(const float& dt)
	{
		sf::Vector2f direction; direction = this->GetDirectionVector();
		this->m_bodysprite.setPosition(this->m_position + direction * this->m_speed * dt);
		this->m_position = this->m_bodysprite.getPosition();

		//impl enemy animations 
		this->WalkAnimation(direction, dt);
	}


private:

	int DamageDealtToEnemy(const sf::FloatRect& object_in_danger_of_collison_with_the_wild_enemy) const
	{
		if (object_in_danger_of_collison_with_the_wild_enemy.contains(m_bodysprite.getPosition()))
		{
			return this->m_damage;
		}

		return NULL;
	}

	bool AttackTimeoutPassed()
	{
		float timePassedSinceLastRestart = this->m_attacktimer.getElapsedTime().asMilliseconds();
		if (timePassedSinceLastRestart > this->m_attackspeed)
		{
			this->m_attacktimer.restart();
			return true;
		}
		this->m_attacktimer.restart();
		return false;
	}

	bool TargetReached()
	{
		if (this->m_position == this->m_target)
		{
			return true;
		}

		if (this->m_health <= 0)
		{
			return true;
		}

		return false;
	}

public: 
	int		p_deflectionRadius = 5; 
	int     u_movementindicator = 0;

private:
	float   m_speed;
	float	m_range; 
	int     m_damage;
	int		m_health;

	sf::Clock   m_attacktimer;
	__int32     m_attackspeed;

	sf::Vector2f m_position;
	sf::Vector2f m_target;

	sf::Sprite  m_bodysprite;
	sf::Texture m_bodytexture;
};