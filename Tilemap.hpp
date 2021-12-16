#include <SFML/Graphics.hpp>
#include "Tile.hpp"
#include "Tileset.hpp"

class IsoTileMap : public sf::Drawable
{
private:
    Tileset *tileset;
    std::vector<std::vector<Tile>> *tiles;
    int mapXSize;
    int mapYSize;

    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const
    {
        // sf::FloatRect v = target.getView().getViewport();
        for (int y = 0; y < mapYSize; y++)
        {
            for (int x = mapXSize - 1; x >= 0; x--)
            {
                if ((*tiles)[x][y].enabled)
                {
                    target.draw((*tiles)[x][y], states);
                }
            }
        }
    }

public:
    void load(int xSize, int ySize, sf::Texture &texture, float tileW, float tileH);
    void loadTilset(int xSize, int ySize, Tileset *tilset, std::vector<std::vector<int>> &map);
    bool collidePoint(sf::Vector2f point)
    {
        for (int y = 0; y < mapYSize; y++)
        {
            for (int x = mapXSize - 1; x >= 0; x--)
            {
                if ((*tiles)[x][y].collidePoint(point))
                {
                    return true;
                }
            }
        }

        return false;
    }
};