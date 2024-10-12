#pragma once
#include <string>
#include <vector>

// Idee: Jede interaktion von 2 objekten sollte hier erfasst werden 
// Problem: Wie werden die events erfasst?

class EventHandler
{
public:
	void AddEvent(const std::string& event)
	{
		m_eventstack.push_back(event); 
	}
	
	void PopEvent(const int& index)
	{
		m_eventstack.erase(m_eventstack.begin() + index);
	}

private: 
	std::vector<std::string> m_eventstack; 
};

