#include <SFML/Graphics.hpp>
// https://www.youtube.com/watch?v=kCIaHqb60Cw

#include "NoizeGenerator.h"
#include "PerlinMath.h"

void NoizeGenerator::Initialize(const int& width, const int& height, const float& scale, const sf::Vector2f& offset)
{
	this->m_width = width;
	this->m_height = height;
	this->m_scale = scale;
	this->m_offset = offset;

	for (int i = 0; i < m_size; i++) { std::vector<Wave> tmp; m_property_waves.push_back(tmp); }

	m_property_waves[0].push_back(Wave(56, 0.05, 1));
	m_property_waves[0].push_back(Wave(199.36, 0.1, 0.5));
	m_property_waves[1].push_back(Wave(621, 0.03, 1));
	m_property_waves[2].push_back(Wave(318, 0.04, 1));
	m_property_waves[2].push_back(Wave(329.7, 0.02, 0.5));

	for (int index = 0; index < m_size; index++)
	{
		std::vector<float> noiseValues;
		noiseValues = Generate(index);
		m_properties.push_back(noiseValues);
	}
}

std::vector<float> NoizeGenerator::Generate(const int& waveIndex)
{
	std::vector<float> noiseMap(m_width * m_height, 0);

	for (int i = 0; i < m_width; i++)
	{
		for (int j = 0; j < m_height; j++)
		{
			int index = j + i * m_height;

			float samplePosX = static_cast<float>(i) * m_scale + m_offset.x;
			float samplePosY = static_cast<float>(j) * m_scale + m_offset.y;

			float normalization = 0.0f;

			for (auto& wave : m_property_waves[waveIndex])
			{
				noiseMap[index] += wave.amplitude * Perlin(samplePosX * wave.frequency + wave.seed, samplePosY * wave.frequency + wave.seed);
				normalization += wave.amplitude;
			}
			noiseMap[index] /= normalization;
			noiseMap[index] = std::abs(noiseMap[index]);

		}
	}


	return noiseMap;
}

std::vector<float> NoizeGenerator::GetBiomValues(const int& index)
{
	std::vector<float> vecToReturn;
	for (int i = 0; i < m_size; i++) {
		vecToReturn.push_back(m_properties[i][index]);
	}
	return vecToReturn;
}


