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

class Enemy : public GameObject
{
public:

	Enemy(const TextureHolder &textures, Textures::ID type) 
		: m_bodysprite(textures.Get(type)), m_type(type)
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
	
	void Initialize(const float& speed, const int& damage, const __int32& attackspeed, const WayPoint& waypoint, const sf::Color& color,int ID)
	{
		LoadAssets(waypoint.position);

		this->m_speed = speed;
		this->p_damage = damage;
		this->m_attackspeed = attackspeed;
		this->m_target = waypoint.target;
		this->m_position = waypoint.position; 
		this->p_ID = ID; 
		this->p_isActive = true; 
		
		objectType = m_type; 
	}

	void Update(const float& dt, Player* player, MapGenerator &map)
	{
		if (!p_health) {
			p_isActive = false; 
			return; 
		}
		m_text.setString(std::to_string(p_health)); 
		m_text.setPosition(m_position); 

		p_hitbox.setPosition(m_position); 

		this->Move(dt, player->GetPosition(), map);

	}

	void Draw(sf::RenderWindow& window) const
	{
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

	sf::FloatRect GetBoundingBox() const override
	{
		return p_hitbox.getGlobalBounds();
	}

	void OnCollision(GameObject& other) override
	{
		Enemy* otherEnemy = dynamic_cast<Enemy*>(&other);
		Entity* otherEntity = dynamic_cast<Entity*>(&other);

		switch (other.objectType)
		{
		case Textures::ID::Zombie:
			HandleEnemyCollision(otherEnemy);
			break; 
		case Textures::ID::House:
			HandleEntityCollision(otherEntity);
			break; 
		case Textures::ID::Spawner:
			HandleEntityCollision(otherEntity);
			break;
		case Textures::ID::Wand_bullet:
			if (LastBulletID != other.objectID) {
				p_health -= 10;
				LastBulletID = other.objectID;
			}
			break; 
		}
		
	}

	void HandleEntityCollision(Entity* entity) {
		// Einfache Absto�ungslogik (basierend auf den Positionen)
		sf::Vector2f direction = m_position - entity->p_position;
		float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
		if (length > 0) {
			direction /= length; // Normalisieren
			m_position += direction * 10.0f;
		}
	}

	void HandleEnemyCollision(Enemy* otherEnemy) {
		// Einfache Absto�ungslogik (basierend auf den Positionen)
		sf::Vector2f direction = m_position - otherEnemy->GetPosition();
		float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
		if (length > 0) {
			direction /= length; // Normalisieren
			m_position += direction * 20.0f;
			otherEnemy->GetPosition() = (otherEnemy->GetPosition() - direction * 3.0f);
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

	void Move(const float& dt, const sf::Vector2f& playerPosition, MapGenerator &map)
	{
		// BFS to get path to player || vorerst nur die richtung zum ersten wegpunkt. 
		//std::vector<sf::Vector2f> path = BFS(m_position, playerPosition, map); 
	
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
				this->m_bodysprite.setPosition(hypotheticalPosition);
			}
			
			m_oncollision = false; 
		}


		//AdjustTileMap(map, hypotheticalPosition); 
		this->m_bodysprite.setPosition(hypotheticalPosition);
		this->m_position = this->m_bodysprite.getPosition();

		//impl enemy animations 
	    this->WalkAnimation(direction, dt);
	}

	void WalkAnimation(const sf::Vector2f& direction, const float &deltatime)
	{	
		if (direction.x == 0 && direction.y == 0) {
			return; 
		}

		if (direction.x > 0 && direction.y < 0) {
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
		
	void AdjustTileMap(MapGenerator& map, const sf::Vector2f& calculatedposition)
	{
		sf::Vector2f tilesize = static_cast<sf::Vector2f>(map.GetTileSize());
		int startX = calculatedposition.x / tilesize.x, endX = GetTextureSize(m_type).x / tilesize.x;
		int startY = calculatedposition.y / tilesize.y, endY = GetTextureSize(m_type).y / tilesize.y;
		int oldX = m_position.x / tilesize.x, oldY = m_position.y / tilesize.y;

		int rangeX = 0, rangeY = 0; 
		if (startY <=0 || endY >= 100) {
			rangeY = 0; 
		}
		if (startX <= 0 || endX >= 100) {
			rangeX = 0;
		}

		for (int i = oldX - rangeX; i < oldX + endX + rangeX; i++) {
			for (int j = oldY - rangeY; j < oldY + endY + rangeY; j++)
			{
				if (map.p_tileMap[i][j].occupationID == m_type) {
					map.p_tileMap[i][j].occupied = false;
					map.p_tileMap[i][j].occupationID = Textures::ID::Undefined;
					map.p_tileMap[i][j].occupierID = -1;
					map.p_tileMap[i][j].tile_sprite.setColor(sf::Color::Magenta);
				}
				
			}
		}

		for (int i = startX - rangeX; i < startX + endX + rangeX; i++) {
			for (int j = startY - rangeY; j < startY + endY + rangeY; j++)
			{
				if (!map.p_tileMap[i][j].occupied) {
					map.p_tileMap[i][j].occupied = true;
					map.p_tileMap[i][j].occupationID = m_type;
					map.p_tileMap[i][j].occupierID = p_ID;
					map.p_tileMap[i][j].tile_sprite.setColor(sf::Color::Yellow); 
				}

			}
		}
	}

	const sf::Vector2f GetTextureSize(Textures::ID ID)
	{
		switch (ID) {
			// Spriteunit should be replaced by individual units in sf::vector2f m_spritesize
		case Textures::ID::Zombie:
			return sf::Vector2f(SPRITEUNIT, SPRITEUNIT);
		}
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



public: 
	sf::RectangleShape p_hitbox; 

	int		p_deflectionRadius = 5; 
	int		p_health = 100;
	int     p_damage = 10;

	int		p_ID = -1; 
	bool    p_isActive = false; 

private:
	bool m_oncollision = false; 

	Textures::ID m_type; 

	sf::Vector2f m_spritesize;

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