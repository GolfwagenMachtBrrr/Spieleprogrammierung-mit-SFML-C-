#include "BiomSetter.h"
#include <iostream>
void BiomeSetter::Initialize()
{
	// Biome sollen sp�ter via Engine hinzugef�gt werden k�nnen.  
	std::cout << "iam here - biosetter init" << std::endl;
	// "Dessert"
	m_biomes.push_back(Biome(1, 0, 0, 0));
	// "Forest"
	m_biomes.push_back(Biome(2,0.05, 0.05, 0.05));
	// "Grassland"
	m_biomes.push_back(Biome(3, 0.2, 0.2, 0.2));
	// "Jungle"
	m_biomes.push_back(Biome(4, 0.3, 0.3, 0.3));
	// "Mountains"
	m_biomes.push_back(Biome(5,0.25, 0.25, 0.25));
	// "Ocean"
	m_biomes.push_back(Biome(6, 0.15, 0.15, 0.15));
	// "Tundra"
	m_biomes.push_back(Biome(7, 0.3, 0.3, 0.3));
}


int BiomeSetter::GetBiome(const float &prop1, const float &prop2, const float &prop3)
{
	std::vector<Biome> possibleBiomes;
	for (auto& i_biome : m_biomes)
	{
		if (i_biome.MatchConditions(prop1, prop2, prop3))
		{
			// std::cout << i_biome.GetID() << " ";
			possibleBiomes.push_back(i_biome);
		}
	}

	Biome biomeToReturn(possibleBiomes[0]);
	float curVal = biomeToReturn.GetDiffVal(prop1, prop2, prop3);

	for (auto &i_biome : possibleBiomes)
	{
		if (i_biome.GetDiffVal(prop1, prop2, prop3))
		{
			biomeToReturn = i_biome; 
			curVal = biomeToReturn.GetDiffVal(prop1, prop2, prop3);
		} 
	}
	return biomeToReturn.GetID();
}
