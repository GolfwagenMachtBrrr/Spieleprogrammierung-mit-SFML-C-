#pragma once
#include "SFML/Graphics.hpp"

class Timer
{
public:

	bool CheckTimer()
	{
		if (this->m_clock.getElapsedTime().asMilliseconds() >= this->m_duration)
		{
			this->m_clock.restart();
			return true;
		}
		return false;
	}

	bool CheckTimerConditional(bool& conditional)
	{
		if (this->m_clock.getElapsedTime().asMilliseconds() >= this->m_duration)
		{
			this->m_clock.restart();
			conditional = true;
			return true;
		}
		return false;
	}

	void CalculateDeltaTime()
	{
		m_deltatime = m_clock.getElapsedTime().asMilliseconds();
		if (m_deltatime != 0) { m_clock.restart(); }
	}

public:
	void SetDuration(int XinMS) { m_duration = XinMS; }
	float GetDeltatime() const noexcept { return m_deltatime; }

private:
	sf::Clock m_clock; 
	sf::Int32 m_duration = 500;
	
	float m_deltatime = 0.0f; 
public:
};