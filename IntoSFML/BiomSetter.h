#pragma once

#include "Bioms.h"
#include <vector>

class BiomeSetter
{

public:

	void Initialize()
	{
		// Biome sollen später via Engine hinzugefügt werden können.  

		// "Dessert"
		m_biomes.push_back(Biome(1, 0.0, 0.0, 0.0));
		// "Forest"
		m_biomes.push_back(Biome(2, 0.01, 0.01, 0.01));
		// "Grassland"
		m_biomes.push_back(Biome(3, 0.03, 0.03, 0.03));
		// "Jungle"
		m_biomes.push_back(Biome(4, 0.04, 0.04, 0.04));
		// "Mountains"
		m_biomes.push_back(Biome(5, 0.25, 0.25, 0.25));
		// "Ocean"
		m_biomes.push_back(Biome(6, 0.15, 0.15, 0.15));
		// "Tundra"
		m_biomes.push_back(Biome(7, 0.3, 0.3, 0.3));
	}

	int GetBiome(std::vector<float> properties)
	{
		std::vector<Biome> possibleBiomes;
		for (auto& i_biome : m_biomes)
		{
			if (i_biome.MatchConditions(properties))
			{
				possibleBiomes.push_back(i_biome);
			}
		}

		Biome biomeToReturn(possibleBiomes[0]);
		float curVal = biomeToReturn.GetDiffVal(properties);

		for (auto& i_biome : possibleBiomes)
		{
			if (i_biome.GetDiffVal(properties))
			{
				biomeToReturn = i_biome;
				curVal = biomeToReturn.GetDiffVal(properties);
			}
		}
		return biomeToReturn.GetID();
	}

private:
	std::vector<Biome> m_biomes;
	int m_size = 3; // Anzahl der "Properties" | Oktaven
};

