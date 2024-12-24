#pragma once
#include "SFML/Graphics.hpp"
#include <random>
#include <vector>
#include <iostream>

#include "Enemy.h"
#include "Player.h"
#include "ResourceHolder.h"
#include "CollisionManager.h"

 // https://www.geeksforgeeks.org/rand-and-srand-in-ccpp/ -> random number between upper&lower bound
// https://www.sfml-dev.org/tutorials/2.6/graphics-text.php

typedef ResourceHolder<sf::Texture, Textures::ID> TextureHolder;

class Spawner : public GameObject, public TimeObject, public Entity
{

public:

	Spawner()
	{}

	void Initialize(const sf::Vector2f &position, std::vector<Textures::ID> &spawntypes, const TextureHolder& textures, CollisionManager* collisionmanager)
	{
		m_sprite.setTexture(textures.Get(Textures::ID::Spawner)); 
		m_sprite.setPosition(position);

		m_font.loadFromFile("C:/Users/JanSa/OneDrive/Desktop/Programmieren/Projekte/ProcMapGen/ProcGen/Assets/Fonts/NotoSansThai-Regular.ttf");
		m_text.setFont(m_font); 
		m_text.setPosition(sf::Vector2f(position.x, position.y-50));

		m_health = 100; 
		m_duration = 2000;

		m_stack = spawntypes; 
		for (int i = 0; i < spawntypes.size(); i++) 
		{ 
			Enemy* enemy = new Enemy();
			m_spawn.push_back(enemy); 
		}
	}
	void Update(const int &deltatime, Player* player, const TextureHolder& textures, CollisionManager* collisionmanager)
	{
		
		if (m_health <= 0)
		{
			KillAllNPCs();
			u_active = false;
		}

		m_text.setString(std::to_string(m_health));
		
		if (this->CheckTimer() && m_stack.size() > 0 && u_active)
		{
			Textures::ID currtype = m_stack[m_stack.size() - 1];
			this->SpawnNPC(player->GetPosition(), currtype, textures, collisionmanager);
		}
		
		for (int i = 0; i < m_spawn.size(); i++)
		{
			m_spawn[i]->Update(deltatime, player);
			if (m_spawn[i]->u_active == false) {
				m_entity_death_count++; 
				m_spawn.erase(m_spawn.begin()+i); 
				break; 
			}
	
		}
		
	}
	void Draw(sf::RenderWindow& window, Player *player)
	{
		if (!u_active) {
			return; 
		}

		if (player->ValidateRendering(m_sprite)) {
			window.draw(m_sprite);
			window.draw(m_text);
		}

		for (auto& enemy : m_spawn)
		{
			if (enemy->p_isActive) {
				enemy->Draw(window, player);
			}
		}
	}

	void OnCollision(GameObject& other) override {}
	
private: 

	void SpawnNPC(const sf::Vector2f &player_position, const Textures::ID &type, const TextureHolder& textures, CollisionManager* collisionmanager)
	{
		if (m_stack.size() == 0) {return;}
		m_enemycount++;
		std::cout << "Im here" << std::endl; 

		switch (type)
		{
		case Textures::ID::Zombie:
			m_spawn[m_stack.size()-1]->Initialize(textures, Textures::ID::Zombie, CalculatePosition()); //stats sollen aus zombie.txt gelesen werden
			collisionmanager->addObject(m_spawn[m_stack.size() - 1]); 
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

		return nPosition;
	}

private:
	int		     m_spawnradius = 400; // not entire radius
	int		     m_enemycount = 0; 

	sf::Font	 m_font; 
	sf::Text     m_text; 

private:
	std::vector<Textures::ID> m_stack; 
public:
	std::vector<Enemy*> m_spawn;
	// Killcount
	int m_entity_death_count = 0;
};

