#pragma once
#include <SFML/Graphics.hpp>

#include <iostream>

class Viewer
{
public: 

	void Initialize(const sf::Vector2f &position, const float &speed, const float &zoom)
	{
		this->m_position = position;
		this->m_speed = speed;	
		this->m_view.setCenter(position); 
		this->m_view.zoom(zoom); 
	}

	void Update(const float &deltatime)
	{
		m_position = m_view.getCenter();

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
			m_position = (m_position + sf::Vector2f(0, -1) * m_speed * deltatime);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
			m_position = (m_position + sf::Vector2f(0, 1) * m_speed * deltatime);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			m_position = (m_position + sf::Vector2f(1, 0) * m_speed * deltatime);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
			m_position = (m_position + sf::Vector2f(-1, 0) * m_speed * deltatime);
		}

		//std::cout << m_position.x << " " << m_position.y << std::endl; 
		m_view.setCenter(m_position);
	}

	void setViewCenter(const sf::Vector2f& position)
	{
		this->m_position = position;
		this->m_view.setCenter(position); 
	}
	
	const sf::Vector2f GetPosition()
	{
		return this->m_position; 
	}

	const sf::View GetView()
	{
		return this->m_view;
	}

private:

	sf::Vector2f m_position;
	sf::View m_view; 
	float m_speed; 
};

