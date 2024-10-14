#pragma once
#include "SFML/Graphics.hpp"
#include "ResourceHolder.h"

typedef ResourceHolder<sf::Texture, Textures::ID> TextureHolder;

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

	Tile(const unsigned int& ID, const unsigned int& BiomID, const TextureHolder &textures, sf::IntRect* TextureRectangle, const sf::Vector2f& TilePosition)
		: tile_ID(ID), tile_Biome(BiomID), tile_sprite(textures.Get(Textures::ID::Grass)), tile_texRect(TextureRectangle), tile_position(TilePosition) {}

	void SetupSprite() 
	{
		this->tile_sprite.setTextureRect(*tile_texRect);
		this->tile_sprite.setPosition(tile_position);
	}

	unsigned int tile_ID;
	unsigned int tile_Biome;

	sf::IntRect* tile_texRect;

	sf::Vector2f tile_position;
	sf::Sprite   tile_sprite;
};
