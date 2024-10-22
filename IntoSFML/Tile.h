#pragma once
#include "SFML/Graphics.hpp"
#include "ResourceHolder.h"

struct Tile
{
	Tile()
	{
		// should throw an error if not initialized & default constructor used
		this->tile_ID = -1;
		this->tile_Biome = -1;
		this->tile_texRect = nullptr;
		this->tile_position = sf::Vector2f(-1, -1);

	}

	Tile(const unsigned int& ID, const unsigned int& BiomID, sf::IntRect* TextureRectangle, const sf::Sprite &sprite, const sf::Vector2f& TilePosition)
		: tile_ID(ID), tile_Biome(BiomID), tile_texRect(TextureRectangle),tile_sprite(sprite), tile_position(TilePosition) {}

	void SetupSprite() 
	{
		tile_sprite.setPosition(tile_position);
		tile_sprite.setTextureRect(*tile_texRect); 
	}

	unsigned int tile_ID;
	unsigned int tile_Biome;

	sf::IntRect* tile_texRect;

	sf::Vector2f tile_position;
	sf::Sprite   tile_sprite;


	int			 occupierID	  = -1; 
	bool		 occupied	  = false; 
	Textures::ID occupationID = Textures::ID::Undefined; 
};
