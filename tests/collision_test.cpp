#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "../src/Tile.hpp"
#include <SFML/Graphics.hpp>

TEST_CASE("Testing collidePoint")
{
    Tile tile;
    sf::Texture texture;
    CHECK_NE(texture.create(100, 100), 0);
    tile.init(texture, sf::IntRect(0, 0, 32, 32));
    tile.setPosition(0.0, 0.0);
    tile.enable();
    tile.enableWalkable();

    for (int i = 1; i < 10; i++)
    {
        CHECK_FALSE(tile.collidePoint(sf::Vector2f(i, 0)));
        CHECK_FALSE(tile.collidePoint(sf::Vector2f(0, i)));
        CHECK_FALSE(tile.collidePoint(sf::Vector2f(i, i)));
    }
}
