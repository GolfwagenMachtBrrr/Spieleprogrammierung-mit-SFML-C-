#pragma once

#include "Bioms.h"
#include <vector>

class BiomeSetter
{

public:

	void Initialize(); 

	int GetBiome(std::vector<float> properties);

private:
	std::vector<Biome> m_biomes;
	int m_size = 3; // Anzahl der "Properties" | Oktaven
};

