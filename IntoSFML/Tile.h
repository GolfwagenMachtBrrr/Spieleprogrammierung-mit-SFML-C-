#pragma once
#include "SFML/Graphics.hpp"

struct Tile
{
	Tile()
	{
		// should throw an error if not initialized & default constructor used
		this->tile_ID = -1;
		this->tile_Biome = -1;
		this->tile_texture = nullptr;
		this->tile_texRect = nullptr;
		this->tile_position = sf::Vector2f(-1, -1);

	}

	Tile(const unsigned int& ID, const unsigned int& BiomID, sf::Texture* Texture, sf::IntRect* TextureRectangle, const sf::Vector2f& TilePosition)
		: tile_ID(ID), tile_Biome(BiomID), tile_texture(Texture), tile_texRect(TextureRectangle), tile_position(TilePosition) {}

	void SetupSprite() 
	{
		this->tile_sprite.setTexture(*tile_texture); 
		this->tile_sprite.setTextureRect(*tile_texRect);
		this->tile_sprite.setPosition(tile_position);
	}

	unsigned int tile_ID;
	unsigned int tile_Biome;

	sf::Texture* tile_texture;
	sf::IntRect* tile_texRect;

	sf::Vector2f tile_position;
	sf::Sprite   tile_sprite;
};
