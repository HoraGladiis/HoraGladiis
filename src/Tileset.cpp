#include "Tileset.hpp"

Tileset::Tileset(std::string tilesetPath, sf::Vector2i tileSize, int tilesCount)
{
    this->tilesetTextute = new sf::Texture();
    this->tilesetTextute->loadFromFile(tilesetPath);
    this->tilestSize = this->tilesetTextute->getSize();
    this->tileSize = tileSize;
    this->tileProportion = (float)this->tileSize.y / (float)this->tileSize.x;
    this->tilesCount = tilesCount;
    std::cout << "Loading: " << tilesetPath << "\n";
    std::cout << "> Tile count: " << tilesCount << "\n";
    std::cout << "> Tile size: " << tileSize.x << "x" << tileSize.y << "\n";
}

Tileset::~Tileset()
{
}

void Tileset::initTile(Tile &tile, int index)
{
    sf::IntRect rect = this->getRectForTile(index);
    tile.init(*this->tilesetTextute, rect);
}

sf::IntRect Tileset::getRectForTile(int index)
{
    index = index % this->tilesCount;

    unsigned int colCount = this->tilestSize.x / this->tileSize.x;
    unsigned int rowCount = this->tilestSize.y / this->tileSize.y;

    int left = this->tileSize.x * (index % colCount);
    int top = this->tileSize.y * ((index / colCount) % rowCount);

    return sf::IntRect(left, top, this->tileSize.x, this->tileSize.y);
}

float Tileset::getTileProportion()
{
    return this->tileProportion;
}