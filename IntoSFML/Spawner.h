#pragma once
#include "Common.h"

#include "Player.h"
#include "Enemy.h"
#include "nRessources.h"
#include "nCollision.h"

// https://www.geeksforgeeks.org/rand-and-srand-in-ccpp/ -> random number between upper&lower bound
// https://www.sfml-dev.org/tutorials/2.6/graphics-text.php


class Spawner : public GameObject
{
public:
	Spawner(Textures::ID tID, Fonts::ID fID, const sf::Vector2f& InitalPosition, int SpawnerID)
		: GameObject(tID, fID, InitalPosition), m_spawnerID(SpawnerID)
	{
		SetupEntity("Spawner" + std::to_string(SpawnerID), 500, 10, 0.125 / 2, 500);

		m_text.setPosition(sf::Vector2f(InitalPosition.x, InitalPosition.y - 50));;
		m_spawnrate.SetDuration(2000);
	}

	void AddToStack(const std::vector<Textures::ID>& newSpawn)
	{
		for (auto spawn : newSpawn)
		{
			m_stack.push_back(spawn);

			Enemy* newEnemy = new Enemy(spawn, Fonts::ID::OnlyFont, CalculatePosition(), sf::IntRect(32 * 0, 32 * 1, 32, 32));
			std::string name = "Zombie" + std::to_string(m_spawn.size()) + std::to_string(m_spawnerID);
			m_spawn.push_back(newEnemy);
		}
	}
	void Update(const int& deltatime, const sf::Vector2f& PlayerPosition)
	{
		if (m_health <= 0)
		{
			KillAllNPCs();
			active = false;
		}

		m_text.setString(std::to_string(m_health));

		if (m_spawnrate.CheckTimer() && m_stack.size() > 0 && active)
		{
			Textures::ID currtype = m_stack[m_stack.size() - 1];
			this->SpawnNPC(PlayerPosition, currtype);
		}

		for (int i = 0; i < m_spawn.size(); i++)
		{
			if (m_spawn[i]->GetHealth() <= 0) {
				m_spawn[i]->active = false;
				GameData::Player::_TotalEnemiesKilled++; 
				m_spawn.erase(m_spawn.begin() + i);
				break;
			}

			if (m_spawn[i]->active)
			{
				m_spawn[i]->Update(deltatime);
			}

		}
	}
	
	void Draw(sf::RenderWindow& window) const noexcept 
	{
		if (!active) { return; }

		if (GameData::Player::ValidateRendering(m_sprite)) {
			window.draw(m_sprite);
			window.draw(m_text);
		}

		for (auto& enemy : m_spawn) { if (enemy->active) { enemy->Draw(window); } }
	}
	void OnCollision(GameObject& other) override
	{
		switch (other.GetObjectTextureID())
		{
		case Textures::ID::Wand_bullet:
			if (other.enabled)
			{
				other.enabled = false;
				m_health -= 10; // There may be a better way
			}
			break;
		default:
			break;
		}
	}
	
private: 
	void SpawnNPC(const sf::Vector2f& player_position, Textures::ID ID)
	{
		if (m_stack.size() == 0) { return; }

		switch (ID)
		{
		case Textures::ID::Zombie:
			m_spawn[m_stack.size() - 1]->active = true;
			m_spawn[m_stack.size() - 1]->PrintEntityStats();
			Collisions::_CollisionManager.addObject(m_spawn[m_stack.size() - 1]);
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
		sf::Vector2f nPosition; int spawnradius = 50;

		int nPosX, nPosY;
		int ubX = m_position.x + spawnradius, lbX = m_position.x - spawnradius;
		int ubY = m_position.y + spawnradius, lbY = m_position.y - spawnradius;

		nPosX = (rand() % (ubX - lbX + 1)) + lbX;
		nPosY = (rand() % (ubY - lbY + 1)) + lbY;

		nPosition.x = std::abs(nPosX);
		nPosition.y = std::abs(nPosY);

		return nPosition;
	}


private:
	int			m_spawnerID; 
	Timer		m_spawnrate;

private:
	std::vector<Textures::ID> m_stack;
	std::vector<Enemy*>       m_spawn;

	int m_entity_death_count = 0;
};

