#pragma once

#include "Bioms.h"
#include <vector>

class BiomeSetter
{

public:
	void Initialize(); 
	int GetBiome(const float& prop1, const float& prop2, const float& prop3);

private:
	std::vector<Biome> m_biomes;
};

