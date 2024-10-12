#pragma once
#include "SFML/Graphics.hpp"
#include "TextureHolder.h"


#include <random>
#include <vector>
#include <iostream>

#include "Enemy.h"
#include "Player.h"

 // https://www.geeksforgeeks.org/rand-and-srand-in-ccpp/ -> random number between upper&lower bound
// https://www.sfml-dev.org/tutorials/2.6/graphics-text.php




class Spawner
{
public:
	enum SpawnType
	{
		ZOMBIE,
		SKELETON,
		BANDIT
	};


public:
	void Initialize(const sf::Vector2f &position, std::vector<SpawnType> &spawntypes, TextureHolder &textureholder)
	{
		m_texture.loadFromFile("C:/Users/JanSa/OneDrive/Desktop/Programmieren/Projekte/ProcMapGen/ProcGen/Assets/AssetPack/Pixel Art Top Down - Basic/Texture/Statue.png");
		m_sprite.setTexture(m_texture);
		m_sprite.setPosition(position);

		m_font.loadFromFile("C:/Users/JanSa/OneDrive/Desktop/Programmieren/Projekte/ProcMapGen/ProcGen/Assets/Fonts/NotoSansThai-Regular.ttf");
		m_text.setFont(m_font); 
		m_text.setPosition(sf::Vector2f(position.x, position.y-50));
	
			
		m_stack = spawntypes; 
		m_textureholder = textureholder; 

		p_hitbox.setPosition(position);
		p_hitbox.setSize((sf::Vector2f)m_texture.getSize());

		for (int i = 0; i < spawntypes.size(); i++) { Enemy enemy;  m_spawn.push_back(enemy); }
	}
	void Update(const int &deltatime, Player &player)
	{
		if (p_health <= 0)
		{
			KillAllNPCs();
			p_isActive = false; 
		}

		m_text.setString(std::to_string(p_health));
		
		for (auto& spawn : m_spawn)
		{
			std::vector<sf::RectangleShape> spawnpositions; 
			for (auto& spawn : m_spawn) {
				spawnpositions.push_back(spawn.p_hitbox);
			}
			spawn.Update(deltatime, player, spawnpositions);
		}

		SpawnType currtype = m_stack[m_stack.size() - 1]; 

		if (this->TimePassed() && m_stack.size() -1 > 0 && p_isActive)
		{
			this->SpawnNPC(player.GetPosition(), currtype);
		}
		
		
	}
	void Draw(sf::RenderWindow& window)
	{
		if (!p_isActive) {
			return; 
		}
		window.draw(m_sprite); 
		window.draw(m_text);

		for (auto& enemy : m_spawn)
		{
			enemy.Draw(window);
		}
	}

	const void addToStack(const SpawnType& enemy)
	{
		m_stack.push_back(enemy);
	}

	bool CheckNPCCollisions(const sf::FloatRect& rect, const int &damage)
	{
		bool bodyHit = false; 
		for (auto &spawn : m_spawn) {
			if (CollisionCheck(rect, spawn.p_hitbox.getGlobalBounds())) {
				spawn.p_health -= damage; 
				bodyHit = true; 
			}
		}

		return bodyHit; 
	}

private: 

	void SpawnNPC(const sf::Vector2f &player_position, const SpawnType &type)
	{

		if (m_stack.size() -1 <= 0)
		{
			return;
		}

		WayPoint wp;
		wp.position = CalculatePosition();
		wp.target = player_position;

		switch (type)
		{
		case Spawner::ZOMBIE:
			m_spawn[m_stack.size() - 1].Initialize(0.125/15, 10, 100, wp, sf::Color::White, m_textureholder); //stats sollen aus zombie.txt gelesen werden
			break;
		case Spawner::SKELETON:
			break;
		case Spawner::BANDIT:
			break;
		default:
			break;
		}

		m_stack.pop_back();
	}
	void KillNPC(const int &NPC_index);
	void KillAllNPCs()
	{
		while (!m_spawn.empty()) {
			m_spawn.pop_back(); 
		}
	}

	sf::Vector2f CalculatePosition() 
	{ 
		sf::Vector2f nPosition; 

		int nPosX, nPosY; 
		int ubX = this->m_position.x + this->m_spawnradius, lbX = this->m_position.x - this->m_spawnradius;
		int ubY = this->m_position.y + this->m_spawnradius, lbY = this->m_position.y - this->m_spawnradius;

		nPosX = (rand() % (ubX - lbX + 1)) + lbX;
		nPosY = (rand() % (ubY - lbY + 1)) + lbY;

		std::cout << nPosX << " " << nPosY << std::endl;

		nPosition.x = std::abs(nPosX); 
		nPosition.y = std::abs(nPosY); 


		return nPosition;
	}

	bool TimePassed()
	{
		int timeellapsed = this->m_clock.getElapsedTime().asMilliseconds();
		if (timeellapsed >= this->m_spawnrate)
		{
			this->m_clock.restart();
			return true;
		}

		return false; 
	}

	bool IsOverlapping(const sf::Vector2f &position)
	{
		for (auto& enemy : m_spawn)
		{
			if (position.x > enemy.GetPosition().x + enemy.p_deflectionRadius,
				position.x < enemy.GetPosition().x - enemy.p_deflectionRadius,
				position.y > enemy.GetPosition().y + enemy.p_deflectionRadius,
				position.y < enemy.GetPosition().y - enemy.p_deflectionRadius)
			{
				return false; 
			}
		}
		return true; 
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

private:
	// Utillity
	sf::Vector2f u_playerposition;
	int		     u_deltatime; 
	int		m_spawnradius = 25; // not entire radius
	int		m_capacity; 
	int		m_enemycount; 

	__int32 m_spawnrate = 2000; 

	sf::Texture	 m_texture; 
	sf::Sprite	 m_sprite; 

	sf::Font	 m_font; 
	sf::Text     m_text; 

	sf::Clock	 m_clock;
	sf::Vector2f m_position; 

private:

	TextureHolder           m_textureholder; 

	std::vector<SpawnType>    m_stack; 
	std::vector<Enemy>		  m_spawn; 

public:

	SpawnType		   p_type;
	int				   p_health = 100;
	bool			   p_isActive = true;
	sf::RectangleShape p_hitbox;
};

