#pragma once
#include "Inventory.h"
#include "ScoreBoard.h"

// TODO

class HUD
{
public:
	void Initalize(); 
	void Update(); 
	void Draw(); 

private: 
	Inventory m_inventory; 
	ScoreBoard m_scoreboard; 
};

