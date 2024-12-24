#pragma once
#include "SFML/Graphics.hpp"

struct Entity
{
public:
	void SetHealth(); 
	void SetDamage(); 
	void SetSpeed(); 
	void SetAttackSpeed(); 
	
	int GetHealth();
	int GetDamage();

	float GetSpeed()
	{
		return m_speed; 
	}

	int GetAttackSpeed();
	
protected: 
	int			     m_health = -1;
	int			     m_damage = -1;
	float		     m_speed  = -1;
	int				 m_attackspeed = -1; 
};

