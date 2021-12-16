#include <SFML/Graphics.hpp>
#include "Tilemap.hpp"
#include "Tileset.hpp"
#include <iostream>
#include <vector>
#include <map>

class GameLevel : public sf::Drawable
{
private:
    std::vector<IsoTileMap> tileLayers;
    std::map<std::string, sf::Texture> textures;
    std::string name;

    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const
    {
        // std::cout << "Drawing level = " << name << std::endl;
        for (IsoTileMap layer : tileLayers)
        {
            target.draw(layer, states);
        }
    }

public:
    void init(std::string name, Tileset *tileset);
    bool collidePoint(sf::Vector2f point)
    {
        for (IsoTileMap layer : tileLayers)
        {
            if (layer.collidePoint(point))
            {
                return true;
            }
        }

        return false;
    }
};
