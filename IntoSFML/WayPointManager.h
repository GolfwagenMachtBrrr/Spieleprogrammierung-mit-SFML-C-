#pragma once
#pragma once
#include "WayPoint.h"
#include <vector>
#include <iostream>

//https://stackoverflow.com/questions/7198144/how-to-draw-a-n-sided-regular-polygon-in-cartesian-coordinates


class WayPointManager
{
public:
	// sample numbers
	WayPointManager() {}

	void Initialize(const sf::Vector2f& wavecenter, const float& radius, const int& sides)
	{
		this->m_epizentrum = wavecenter, this->m_radius = radius, this->m_sides = sides;
		this->AddWave();
	}

	const void AddWave()
	{
		int angle_increment = 360 / m_sides;
		int angle = angle_increment;

		for (int i = 1; i <= m_sides; i++)
		{
			float startPointPosX = m_epizentrum.x + m_radius * std::cos(angle),
				startPointPosY = m_epizentrum.y + m_radius * std::sin(angle);

			std::cout << "Start: " << (int)startPointPosX << " " << (int)startPointPosY << std::endl;

			WayPoint waypoint;
			waypoint.isActive = true;
			waypoint.position = sf::Vector2f(startPointPosX, startPointPosY);

			float targetPointPosX = m_epizentrum.x + m_radius * std::cos(angle * m_sides/2),
				targetPointPosY = m_epizentrum.y + m_radius * std::sin(angle * m_sides/2);

			waypoint.target = sf::Vector2f(targetPointPosX, targetPointPosY);

			std::cout << "Target: " << (int)targetPointPosX << " " << (int)targetPointPosY << std::endl;

			angle += angle_increment;

			p_wavepoints.push_back(waypoint);
		}

	}

	void Draw(sf::RenderWindow& window)
	{
		sf::VertexArray linchenmachtaufBadBitch(sf::LinesStrip, 2 * m_sides);
		for (int i = 0; i < m_sides; i+=2)
		{
			linchenmachtaufBadBitch[i] = p_wavepoints[i].position;
			linchenmachtaufBadBitch[i + 1] = p_wavepoints[i].target;
			linchenmachtaufBadBitch[i].color = sf::Color::Blue;
			linchenmachtaufBadBitch[i + 1].color = sf::Color::Red;

		}
		window.draw(linchenmachtaufBadBitch);
	}

public:
	std::vector<WayPoint> p_wavepoints;

private:
	void ClearWave()
	{
		this->p_wavepoints.clear();
	}

private:
	sf::Vector2f m_epizentrum;

	int m_radius;
	int m_sides;

};