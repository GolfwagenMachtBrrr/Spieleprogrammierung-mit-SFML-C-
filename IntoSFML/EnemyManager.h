#pragma once
#include "SFML/Graphics.hpp"
#include "WayPointManager.h"
#include "Enemy.h"

#include <vector>

class EnemieManager
{
public:

	EnemieManager() {}

	void Initialize(const sf::Vector2f& center)
	{
		this->m_waypoints.Initialize(center, 1000, 24);
		std::cout << this->m_waypoints.p_wavepoints.size() << " size waypoints " << std::endl; 
		for (int i = 0; i < this->m_waypoints.p_wavepoints.size(); i++)
		{
			for (int j = 0; j < this->m_concentration; j++)
			{
				// die Werte für unterschiedliche gegner sollten aus einer Datei gelesen werden.
				//Enemy enemy; enemy.Initialize(0.125 / 5 * (j + 1), 10, 500, this->m_waypoints.p_wavepoints[i], sf::Color::Blue);
				//this->m_enemies.push_back(enemy);
			}
		}
	}
	// TODO add playerInfoStruct
	void Update(const float& dt, const sf::Vector2f& playerPosition, const sf::FloatRect& playerHitbox)
	{
		//for (auto& enemy : this->m_enemies) { enemy.Update(dt, playerPosition, playerHitbox); }
	}
	void Draw(sf::RenderWindow& window)
	{
		this->m_waypoints.Draw(window);
		for (auto& enemy : this->m_enemies) { enemy.Draw(window); }
	}

	void AddWave()
	{
		this->m_waypoints.AddWave();
	}

private:

	int m_concentration = 5; // enemies per waypoint 
	int m_wave_complexity; // keep count of waypoints 
	int m_wavecount;

	std::vector<Enemy> m_enemies;
	WayPointManager m_waypoints;

};