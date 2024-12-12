#pragma once
#include "SFML/Graphics.hpp"
#include "Bullet.h"
#include "Spawner.h"
#include "MapManager.h"
#include <vector>

class Gun
{
public: 

	enum CollisionType
	{
		COLLISION_NONE = NULL, 
		ENTITY_COLLISION,
		ENEMY_COLLISION,
	};

	Gun(){}

	void Update(const float& dt, const sf::Vector2f& player_position, const sf::Vector2f& mouse_position, MapManager& mapm);
	void Draw(sf::RenderWindow& window); 

private:
	void CreateBulletTarget(const int& index, const sf::Vector2f& mousePos);
	const bool GetAttackTimer(); 
	
private: 
	std::vector<Bullet> m_bullets; 

	sf::Clock m_attacktimer; 
	sf::Int32 m_attacktimermax = 300; 

	// TO ADD: Bullet Animation | texture

public: 

	bool		        p_bulletReachedTarget; 
	sf::RectangleShape  p_bulletTarget; 

	int damage = 10; 
};

