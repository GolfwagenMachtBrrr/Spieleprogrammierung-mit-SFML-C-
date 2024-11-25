#pragma once
#include "SFML/Graphics.hpp"
#include <random>
#include <vector>
#include <iostream>

#include "Enemy.h"
#include "Player.h"
#include "ResourceHolder.h"

 // https://www.geeksforgeeks.org/rand-and-srand-in-ccpp/ -> random number between upper&lower bound
// https://www.sfml-dev.org/tutorials/2.6/graphics-text.php




typedef ResourceHolder<sf::Texture, Textures::ID> TextureHolder;

class Spawner
{


public:

	Spawner()
	{}

	void Initialize(const sf::Vector2f &position, std::vector<Textures::ID> &spawntypes, const TextureHolder& textures)
	{
		m_sprite.setTexture(textures.Get(Textures::ID::Spawner)); 
		m_sprite.setPosition(position);

		m_font.loadFromFile("C:/Users/JanSa/OneDrive/Desktop/Programmieren/Projekte/ProcMapGen/ProcGen/Assets/Fonts/NotoSansThai-Regular.ttf");
		m_text.setFont(m_font); 
		m_text.setPosition(sf::Vector2f(position.x, position.y-50));

		p_hitbox.setPosition(position);
		p_hitbox.setSize((sf::Vector2f)textures.Get(Textures::ID::Spawner).getSize());

		m_stack = spawntypes; 
		for (int i = 0; i < spawntypes.size(); i++) { Enemy enemy(textures, spawntypes[i]); m_spawn.push_back(enemy); }
	}
	void Update(const int &deltatime, Player &player, MapGenerator &map)
	{
		
		if (p_health <= 0)
		{
			KillAllNPCs();
			p_isActive = false; 
		}

		m_text.setString(std::to_string(p_health));
		
		if (this->TimePassed() && m_stack.size() > 0 && p_isActive)
		{
			Textures::ID currtype = m_stack[m_stack.size() - 1];
			this->SpawnNPC(player.GetPosition(), currtype);
		}
		
		for (auto& spawn : m_spawn)
		{
			spawn.Update(deltatime, player, map);
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
			if (enemy.p_isActive) {
				enemy.Draw(window);
			}
		}
	}

	const void addToStack(const Textures::ID& enemy)
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

	void SpawnNPC(const sf::Vector2f &player_position, const Textures::ID &type)
	{
		if (m_stack.size() == 0)
		{
			return;
		}

		WayPoint wp;
		wp.position = CalculatePosition();
		wp.target = player_position;

		m_enemycount++;

		switch (type)
		{
		case Textures::ID::Zombie:
			m_spawn[m_stack.size()-1].Initialize(0.125/2, 10, 100, wp, sf::Color::White, m_enemycount); //stats sollen aus zombie.txt gelesen werden
			break;
		case Textures::ID::Skeleton:
			break;
		case Textures::ID::Bandit:
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

		nPosition.x = std::abs(nPosX); 
		nPosition.y = std::abs(nPosY); 

		//std::cout << nPosition.x << " " << nPosition.y << std::endl; 

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
	int		     m_spawnradius = 400; // not entire radius
	int		     m_capacity = 0; 
	int		     m_enemycount = 0; 

	__int32 m_spawnrate = 2000; 

	sf::Sprite	 m_sprite;
	sf::Sprite	 m_spawnsprite; 

	sf::Font	 m_font; 
	sf::Text     m_text; 

	sf::Clock	 m_clock;
	sf::Vector2f m_position; 

private:

	std::vector<Textures::ID>    m_stack; 
	std::vector<Enemy>		  m_spawn; 

public:

	Textures::ID	   p_type;
	int				   p_health = 100;
	bool			   p_isActive = true;
	sf::RectangleShape p_hitbox;
};

