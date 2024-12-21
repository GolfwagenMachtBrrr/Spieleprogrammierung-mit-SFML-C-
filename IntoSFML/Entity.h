#pragma once
#include "SFML/Graphics.hpp"

class Entity
{
	// Evntuell noch Getter und Setter. 
	void DoStuff(); 


protected: 
	int			     m_health = -1;
	int			     m_damage = -1;
	float		     m_speed  = -1;
	int				 m_attackspeed = -1; 

	sf::Font m_text; 


};

