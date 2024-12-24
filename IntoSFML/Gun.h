#pragma once
#include "SFML/Graphics.hpp"

#include "Bullet.h"

#include "CollisionManager.h"
#include "TimeObject.h"

#include <vector>
#include <deque>


class Gun : public TimeObject
{
public: 
	Gun()
	{
		m_duration = 300; 
	}

	void Update(const float& dt,
				const sf::Vector2f& player_position,
				const sf::Vector2f& mouse_position,
				const TextureHolder& textures,
				CollisionManager* collisionmanager);

	void Draw(sf::RenderWindow& window); 

private:
	void CreateBulletTarget(const int& index, const sf::Vector2f& mousePos);
	
private: 
	std::deque<Bullet* > m_bullets; 

	// TO ADD: Bullet Animation | texture

public: 

	bool		        p_bulletReachedTarget; 
	sf::RectangleShape  p_bulletTarget; 
	int damage = 10; 
	
	bool isActive = true; 
};

