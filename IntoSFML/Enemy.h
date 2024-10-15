#pragma once
#include "SFML/Graphics.hpp"
#include "WayPoint.h"
#include "ResourceHolder.h"
#include "Player.h"
#include <string>

#include <iostream>

#define SPRITEUNIT 32
#define MOVEMENT 1

#define FORWARD 7
#define LEFTWARD 3
#define BACKWARD 1
#define RIGHTWARD 5

typedef ResourceHolder<sf::Texture, Textures::ID> TextureHolder;

class Enemy
{
public:

	Enemy(const TextureHolder &textures) 
		: m_bodysprite(textures.Get(Textures::ID::Zombie))
	{}

	void LoadAssets(const sf::Vector2f &startingPos)
	{
		this->m_bodysprite.setTextureRect(sf::IntRect(32*0, 32*1, 32, 32));
		this->m_bodysprite.setPosition(startingPos);

		this->m_font.loadFromFile("C:/Users/JanSa/OneDrive/Desktop/Programmieren/Projekte/ProcMapGen/ProcGen/Assets/Fonts/NotoSansThai-Regular.ttf");
		this->m_text.setFont(m_font); 
		this->m_text.setCharacterSize(10); 
		
		p_hitbox.setSize(sf::Vector2f(32, 32)); 
		p_hitbox.setPosition(startingPos); 
		p_hitbox.setOutlineColor(sf::Color::Red);
		p_hitbox.setOutlineThickness(1);
		p_hitbox.setFillColor(sf::Color::Transparent);
	}
	
	void Initialize(const float& speed, const int& damage, const __int32& attackspeed, const WayPoint& waypoint, const sf::Color& color, const int &ID)
	{
		LoadAssets(waypoint.position);

		this->m_speed = speed;
		this->p_damage = damage;
		this->m_attackspeed = attackspeed;
		this->m_target = waypoint.target;
		this->m_position = waypoint.position; 
		this->p_ID = ID; 
	}

	void Update(const float& dt, Player &player, std::vector<sf::RectangleShape> &spawnpositions)
	{
		m_text.setString(std::to_string(p_health)); 
		m_text.setPosition(m_position); 

		p_hitbox.setPosition(m_position); 

		this->Move(dt, player.GetPosition(), spawnpositions);
		if (this->AttackTimeoutPassed())
		{
			if (CollisionCheck(player.p_hitbox.getGlobalBounds(), p_hitbox.getGlobalBounds())) {
				player.p_health -= p_damage; 
				std::cout << player.p_health << std::endl; 
			}
			 
		}
	}

	void Draw(sf::RenderWindow& window) const
	{
		if (p_health <= 0) {
			return; 
		}
		window.draw(m_bodysprite);
		window.draw(p_hitbox);
		window.draw(m_text);
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

	void Move(const float& dt, const sf::Vector2f& playerPosition, std::vector<sf::RectangleShape>& spawnpositions)
	{
		sf::Vector2f direction; direction = this->GetDirectionVector(playerPosition);

		sf::Vector2f	   hypotheticalPosition = m_position + direction * dt * m_speed;
		sf::RectangleShape hypotheticalHitbox = p_hitbox;

		hypotheticalHitbox.setPosition(hypotheticalPosition); 

		if (CollidesWithAlly(spawnpositions, hypotheticalHitbox) != -1) {
			int DontDoItJan = rand() % 10;

			if (DontDoItJan <= 5) {
				direction = sf::Vector2f(0, 0); 
			}
			else
			{
				direction.x *= (-1);
				direction.y *= (-1);
			}

		}
		
		this->m_bodysprite.setPosition(this->m_position + direction * this->m_speed * dt);
		this->m_position = this->m_bodysprite.getPosition();

		//impl enemy animations 
	    this->WalkAnimation(direction, dt);
	}

	void WalkAnimation(const sf::Vector2f& direction, const float &deltatime)
	{	

		if (direction.x > 0 && direction.y < 0) {
		
			//std::cout << "Forward" << std::endl; 

			m_bodysprite.setTextureRect(sf::IntRect((u_movementindicator / MOVEMENT) * SPRITEUNIT, FORWARD*SPRITEUNIT, SPRITEUNIT, SPRITEUNIT));
			u_movementindicator++;
			if (u_movementindicator / MOVEMENT == 3) {
				u_movementindicator = 0;
			}
		}

		else if (direction.x > 0 && direction.y > 0 && direction.x < direction.y) {

			//std::cout << "Backward" << std::endl;

			m_bodysprite.setTextureRect(sf::IntRect((u_movementindicator / MOVEMENT) * SPRITEUNIT, BACKWARD * SPRITEUNIT, SPRITEUNIT, SPRITEUNIT));
			u_movementindicator++;
			if (u_movementindicator / MOVEMENT == 3) {
				u_movementindicator = 0;
			}
		}

		else if (direction.x < 0 && direction.y > 0) {

			//std::cout << "Leftward" << std::endl;

			m_bodysprite.setTextureRect(sf::IntRect((u_movementindicator / MOVEMENT) * SPRITEUNIT, LEFTWARD * SPRITEUNIT, SPRITEUNIT, SPRITEUNIT));
			u_movementindicator++;
			if (u_movementindicator / MOVEMENT == 3) {
				u_movementindicator = 0;
			}
		}

		else if (direction.x > 0 && direction.y > 0 && direction.x > direction.y) {

			//std::cout << "Rightward" << std::endl;

			m_bodysprite.setTextureRect(sf::IntRect((u_movementindicator/MOVEMENT) * SPRITEUNIT, RIGHTWARD * SPRITEUNIT, SPRITEUNIT, SPRITEUNIT));
			u_movementindicator++;
			if (u_movementindicator / MOVEMENT == 3) {
				u_movementindicator = 0;
			}
		}

		
	}


private:

	int CollidesWithAlly(const std::vector<sf::RectangleShape>& alliedHitbox, const sf::RectangleShape hitbox)
	{
		int collisionID = -1; 
		for (int i = 0; i < alliedHitbox.size(); i++) {
			//std::cout << alliedHitbox[i].getPosition().x << " " << alliedHitbox[i].getPosition().x << "im" << std::endl;

			if (CollisionCheck(alliedHitbox[i].getGlobalBounds(), hitbox.getGlobalBounds()) && i != p_ID) {
				collisionID = i; 
			}
		}
		return collisionID; 
	}

	bool CollisionCheck(const sf::FloatRect& a, const sf::FloatRect& b)
	{
		if (a.left + a.width > b.left &&
			b.left + b.width > a.left &&
			b.top + b.height > a.top &&
			a.top + a.height > b.top)
		{
			return true;
		}
		return false;
	}

	int DamageDealtToEnemy(const sf::FloatRect& object_in_danger_of_collison_with_the_wild_enemy) 
	{
		if (CollisionCheck(object_in_danger_of_collison_with_the_wild_enemy, p_hitbox.getGlobalBounds()))
		{
			std::cout << p_damage << std::endl;
			return this->p_damage;
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

		if (this->p_health <= 0)
		{
			return true;
		}

		return false;
	}

public: 
	sf::RectangleShape p_hitbox; 

	int		p_deflectionRadius = 5; 
	int		p_health = 100;
	int     p_damage = 10;

	int		p_ID = -1; 

private:

	int     u_movementindicator = 0;

	float   m_speed;
	float	m_range; 


	sf::Clock   m_attacktimer;
	__int32     m_attackspeed;

	sf::Vector2f m_position;
	sf::Vector2f m_target;

	sf::Sprite  m_bodysprite;

	sf::Font m_font; 
	sf::Text m_text; 
};