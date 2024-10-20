#pragma once
#include <iostream>
#include <vector>

// valueScope == Intervall an Noise Werten in denen das Biom gilt
//Rendering TileMap - https://www.youtube.com/watch?v=zqG3bEl3h20

class Biome
{
public:

	Biome()
		: m_ID(-1)
	{}

	Biome(const unsigned int &ID, const float& val, const float& val1, const float& val2)
		: m_ID(ID)
	{
		this->m_valueScopes.push_back(val);
		this->m_valueScopes.push_back(val1);
		this->m_valueScopes.push_back(val2);
	}


	float GetDiffVal(const std::vector<float> &properties)
	{
		float difference = 0;
		for (int i = 0; i < m_size; i++)
		{
			difference += (properties[i] - m_valueScopes[i]);
		}
		return difference; 
	}

	bool MatchConditions(const std::vector<float> &properties)
	{
		for (int i = 0; i < m_size; i++)
		{
			if (properties[i] < m_valueScopes[i])
			{
				return false;
			}
		}
		return true;
	}

	int GetID()
	{
		return this->m_ID;
	}

private:

	int m_ID;
	int m_size = 3; 
	std::vector<float> m_valueScopes; 
};


