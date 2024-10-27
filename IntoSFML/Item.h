#pragma once
#include "SFML/Graphics.hpp"
#include "ResourceHolder.h"

struct Item
{
	Item()
	{}

	Item(const Textures::ID ID, sf::Vector2f* Position, sf::RectangleShape* Hitbox)
		: id(ID), position(Position), hitbox(hitbox)
	{}

	// Sollten die nicht eine textur haben? 

	Textures::ID		 id		  = static_cast<Textures::ID>(-1); 
	sf::Vector2f*		 position = new sf::Vector2f(); 
	sf::RectangleShape*	 hitbox   = new sf::RectangleShape();
	bool				 isActive = false; 


};