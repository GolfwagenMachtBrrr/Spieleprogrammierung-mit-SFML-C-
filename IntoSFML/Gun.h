#pragma once
#include "SFML/Graphics.hpp"
#include "Bullet.h"
#include <vector>

class Gun
{
public: 
	Gun() : m_attacktimermax(300) {}

	void Update(const float& dt, const sf::Vector2f& player_position, const sf::Vector2f& mouse_position);
	void Draw(sf::RenderWindow& window); 

private:
	void CreateBulletTarget(const int& index, const sf::Vector2f& mousePos);
	const bool GetAttackTimer(); 
private: 
	std::vector<Bullet> m_bullets; 

	sf::Clock m_attacktimer; 
	sf::Int32 m_attacktimermax; 

	// TO ADD: Bullet Animation | texture

};

