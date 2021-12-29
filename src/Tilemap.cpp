#include "Tilemap.hpp"

void IsoTileMap::load(int xSize, int ySize, sf::Texture &texture, float tileW, float tileH)
{
    mapXSize = xSize;
    mapYSize = ySize;
    float tileProportion = tileH / tileW;

    tiles = new std::vector<std::vector<Tile>>(xSize, std::vector<Tile>(ySize, Tile()));

    for (int x = 0; x < xSize; x++)
    {
        for (int y = 0; y < ySize; y++)
        {
            float centerX = (x * tileW / 2) + (y * tileW / 2);
            float centerY = (y * tileH / (4 * tileProportion)) - (x * tileH / (4 * tileProportion));
            (*tiles)[x][y].init(texture, sf::IntRect(0, 0, tileW, tileH));
            (*tiles)[x][y].setPosition(centerX, centerY);
        }
    }
}

void IsoTileMap::loadTilset(int xSize, int ySize, Tileset *tileset, std::vector<std::vector<int>> &map)
{
    this->tileset = tileset;
    mapXSize = xSize;
    mapYSize = ySize;

    sf::Vector2i tileSize = tileset->getTileSize();
    int tileW = tileSize.x;
    int tileH = tileSize.y;

    float tileProportion = this->tileset->getTileProportion();

    tiles = new std::vector<std::vector<Tile>>(xSize, std::vector<Tile>(ySize, Tile()));

    int mapW = map.size();

    for (int x = 0; x < xSize; x++)
    {
        for (int y = 0; y < ySize; y++)
        {
            float centerX = (x * tileW / 2) + (y * tileW / 2);
            float centerY = (y * tileH / (4 * tileProportion)) - (x * tileH / (4 * tileProportion));

            if (x >= 0 && x < mapW)
            {
                int colH = map[x].size();
                if (y >= 0 && y < colH)
                {
                    (*tiles)[x][y].disable();
                    if (map[x][y] != -1)
                    {
                        (*tiles)[x][y].enableWalkable();

                        tileset->initTile((*tiles)[x][y], map[x][y]);
                        if (map[x][y] == 10 || map[x][y] == 2)
                        {
                            (*tiles)[x][y].disableWalkable();
                        }
                    }
                }
            }

            (*tiles)[x][y].setPosition(centerX, centerY);
        }
    }
}