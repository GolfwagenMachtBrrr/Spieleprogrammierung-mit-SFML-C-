#pragma once
#include "Wave.h"

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>



class NoizeGenerator
{	
public: 

	void Initialize(const int& width, const int& height, const float& scale, const sf::Vector2f& offset);

	std::vector<float> Generate(const int& waveIndex);
	std::vector<float> GetBiomValues(const int& index);
	
private:
	std::vector<std::vector<float>> m_properties;
	std::vector<std::vector<Wave>> m_property_waves;

	int m_size = 3; // Anzahl der eigenschaften -> Oktaven 
	int m_width; 
	int m_height; 
	int m_scale; 
	
	sf::Vector2f m_offset; // problaby unötig
};

