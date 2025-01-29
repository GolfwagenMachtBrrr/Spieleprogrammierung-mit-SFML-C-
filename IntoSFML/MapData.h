#pragma once
#include <string>

struct MapData
{
	std::string tilesheet = "";
	std::string name = "";

	int version;
	bool isUsed;

	int tilewidth = 0;
	int tileheight = 0;
	int scalex = 0;
	int scaley = 0;

	int dataSizeX = 0;
	int dataSizeY = 0;
	// <- Beim ausgeben; welche "Dimension hat es" z.b 2,2,2 
	//												   3,3,3
	//												   4,4,4
	// wäre dataSizeY = 3, dataSizeY = 3 .... 
	int datalength = 0;
	int* data = nullptr;
};