#pragma once
#include "Enemy.h"

// move is not in base class because of different behaviour when encountering player contact


class Enemy_High : public Enemy
{
public:
	void Attack1();
	void Attack2();
	void Attack3();

	int Update(const float& dt, const sf::Vector2f& playerPosition, const sf::FloatRect& playerHitbox)
	{
		this->Move(dt, playerPosition);
		if (this->AttackTimeoutPassed())
		{
			return this->DamageDealtToEnemy(playerHitbox);
		}
		return 0;
	}

	int Update(const float& dt)
	{
		this->Move(dt);
		return 0;
	}


private:

	void Move(const float& dt, const sf::Vector2f& playerPosition)
	{
		sf::Vector2f direction; direction = this->GetClosestTarget(this->m_target, playerPosition);
		this->m_body.setPosition(this->m_position + direction * this->m_speed * dt);
		this->m_position = this->m_body.getPosition();

		//impl enemy animations 
	}

	void Move(const float& dt)
	{
		sf::Vector2f direction; direction = this->GetDirectionVector();
		this->m_body.setPosition(this->m_position + direction * this->m_speed * dt);
		this->m_position = this->m_body.getPosition();

		//impl enemy animations 
	}


};