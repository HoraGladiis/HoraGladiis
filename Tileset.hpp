#ifndef TILESET_HPP
#define TILESET_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include "Tile.hpp"
#include "misc.hpp"

class Tileset
{
private:
    sf::Texture *tilesetTextute;
    int tilesCount;
    sf::Vector2u tilestSize;
    float tileProportion;
    sf::Vector2i tileSize;
    sf::IntRect getRectForTile(int index);

public:
    Tileset(std::string tilesetPath, sf::Vector2i tileSize, int tilesCount);
    ~Tileset();
    void initTile(Tile &tile, int index);
    float getTileProportion();
    sf::Vector2i getTileSize()
    {
        return tileSize;
    }
};

#endif // TILESET_HPP