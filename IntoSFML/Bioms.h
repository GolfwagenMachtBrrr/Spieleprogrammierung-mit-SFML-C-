#pragma once
#include <iostream>

class Biome
{
public:

	Biome()
		: m_minProperty1(-1), m_minProperty2(-1), m_minProperty3(-1), m_ID(-1)
	{}

	Biome(int ID, float minPropertyVal1, float minPropertyVal2, float minPropertyVal3)
		: m_minProperty1(minPropertyVal1), m_minProperty2(minPropertyVal2), m_minProperty3(minPropertyVal3), m_ID(ID)
	{}


	float GetDiffVal(const float& valProperty1, const float& valProperty2, const float& valProperty3)
	{
		return (valProperty1 - m_minProperty1) + (valProperty2 - m_minProperty2) + (valProperty3 - m_minProperty3);
	}

	bool MatchConditions(const float &valProperty1, const float &valProperty2, const float &valProperty3)
	{
		if (valProperty1 >= m_minProperty1 && valProperty2 >= m_minProperty2 && valProperty3 >= m_minProperty3)
		{
			return true; 
		}
		return false;
	}

	int GetID()
	{
		return m_ID;
	}

private:
	int m_ID;

	float m_minProperty1;
	float m_minProperty2;
	float m_minProperty3;

};


