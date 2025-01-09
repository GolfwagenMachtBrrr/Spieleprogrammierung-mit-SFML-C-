#pragma once
#include "SFML/Graphics.hpp"

namespace Utility
{
	const static sf::Vector2f Normalize(sf::Vector2f a)
	{
		float m = sqrt(a.x * a.x + a.y * a.y);
		sf::Vector2f normalizedVector;

		normalizedVector.x = a.x /= m;
		normalizedVector.y = a.y /= m;

		return normalizedVector;
	}

	static float CalculateDistance(const Vector2f& src, const Vector2f& dst)
	{
		float nDistanceX = (dst.x - src.x) * (dst.x - src.x);
		float nDistanceY = (dst.y - src.y) * (dst.y - src.y);
		return sqrt(nDistanceX + nDistanceY);
	}

	const static float CalculateAngleInDegrees(const sf::Vector2f& target, const sf::Vector2f& source)
	{
		float rotation = std::atan2(target.x - source.x, target.y - source.y);
		rotation *= (180 / 3.14); 
		rotation += 180; 
		return rotation; 
	}
}