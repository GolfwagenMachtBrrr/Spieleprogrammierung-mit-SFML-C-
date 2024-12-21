#pragma once
#include "SFML/Graphics.hpp"

class TimeObject
{
public:

	virtual bool CheckTimer()
	{
		if (this->m_clock.getElapsedTime().asMilliseconds() >= this->m_duration)
		{
			this->m_clock.restart();
			return true;
		}
		return false;
	}

protected:
	sf::Clock m_clock; 
	sf::Int32 m_duration = 500;
};