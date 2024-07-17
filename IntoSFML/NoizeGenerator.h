#pragma once
#include "Wave.h"

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>



class NoizeGenerator
{	
public: 
	std::vector<float> Generate(const int& width, const int& height, const float& scale, const std::vector<Wave>& waves, const sf::Vector2f& offset);
private:

};

