#pragma once
#include "MapData.h"
#include <fstream>


class MapDataManager
{
public:
	void Initialize(); 
	void Load(); 

	void Save()
	{
		std::ofstream file(("C:/Users/JanSa/Game/IntoSFML_Bilder/Maps/Level2.rmap"));

		file << "[Map]" << std::endl;
		file << "version=" + std::to_string(m_mapdata.version) << std::endl;
		file << "tilesheet=" + m_mapdata.tilesheet << std::endl;
		file << "name=" + m_mapdata.name << std::endl;
		file << "tilewidth=" + std::to_string(m_mapdata.tilewidth) << std::endl;
		file << "tileheight=" + std::to_string(m_mapdata.tileheight) << std::endl;
		file << "scalex=" + std::to_string(m_mapdata.scalex) << std::endl;
		file << "scaley=" + std::to_string(m_mapdata.scaley) << std::endl;
		file << "datalength=" + std::to_string(m_mapdata.datalength) << std::endl;
		file << "dataSizeY=" + std::to_string(m_mapdata.dataSizeY) << std::endl;
		file << "dataSizeX=" + std::to_string(m_mapdata.dataSizeX) << std::endl;

		file << "data= ";
		for (int i = 0; i < m_mapdata.datalength; i++)
		{
			file << std::to_string(m_mapdata.data[i]) << ", ";
		}
		file << std::endl;
	}


private: 
	MapData m_mapdata; 
};