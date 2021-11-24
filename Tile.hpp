#ifndef TILE_HPP
#define TILE_HPP

#include <SFML/Graphics.hpp>
#include <iostream>

class Tile : public sf::Sprite
{
private:
    float centerX;
    float centerY;
    sf::Vector2f center;

public:
    void init(sf::Texture &texture, sf::IntRect rect);
    sf::Vector2f getCenter();
    bool enabled = false;
    bool walkable = true;

    void enable()
    {
        enabled = true;
    }

    void disable()
    {
        enabled = false;
    }

    void enableWalkable()
    {
        walkable = true;
    }

    void disableWalkable()
    {
        walkable = false;
    }
};

#endif // TILE_HPP