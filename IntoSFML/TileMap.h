#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

// https://www.sfml-dev.org/tutorials/2.6/graphics-vertex-array.php
// von "Triangle auf Quad geändert"


class TileMap : public sf::Drawable, public sf::Transformable
{
public:
    
    bool load(const std::string& tileset)
    {
        if (!m_tileset.loadFromFile(tileset))
        {

            return false;
        }
        else
        {
            std::cout << "Tilesheet loaded succesfully" << std::endl; 
        }
    }

    bool CreateTileMap(const std::string& tileset, const sf::Vector2u &tileSize, const std::vector<int> &tiles, unsigned int fromX, unsigned int fromY, unsigned int toX, unsigned int toY)
    {
        // resize the vertex array to fit the level size
        m_vertices.setPrimitiveType(sf::Triangles);
        m_vertices.resize(tiles.size() * 6);

        // populate the vertex array, with two triangles per tile
        for (int i = fromX; i < toX; ++i)
            for (int j = fromY; j < toY; ++j)
            {
                // get the current tile number
                int tileNumber = tiles[j + i * (toY-fromY)];

                // find its position in the tileset texture
                int tu = tileNumber % (m_tileset.getSize().x / tileSize.x);
                int tv = tileNumber / (m_tileset.getSize().x / tileSize.x);

                // get a pointer to the triangles' vertices of the current tile
          
                sf::Vertex* triangles = &m_vertices[ ( (j + i * (toY-fromY) ) * 6)];
           
                // define the 6 corners of the two triangles
                triangles[0].position = sf::Vector2f(i * tileSize.x, j * tileSize.y);
                triangles[1].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
                triangles[2].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);
                triangles[3].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);
                triangles[4].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
                triangles[5].position = sf::Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y);

                // define the 6 matching texture coordinates
                triangles[0].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
                triangles[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
                triangles[2].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
                triangles[3].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
                triangles[4].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
                triangles[5].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
            }

        return true;
    }


private:

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {

        // apply the tileset texture
        states.texture = &m_tileset;

        // draw the vertex array
        target.draw(m_vertices, states);
    }

    sf::VertexArray m_vertices;
    sf::Texture m_tileset;
};
