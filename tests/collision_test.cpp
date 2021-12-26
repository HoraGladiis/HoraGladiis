#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "../src/Tile.hpp"
#include <SFML/Graphics.hpp>

TEST_CASE("Testing collidePoint")
{
    Tile tile;
    sf::Texture texture;
    CHECK_NE(texture.create(10, 10), 0);
    tile.init(texture, sf::IntRect(0, 0, 10, 10));
    tile.setPosition(0.0, 0.0);
    tile.enable();
    tile.enableWalkable();

    CHECK_FALSE(tile.collidePoint(sf::Vector2f(4.0, 2.0)));
}
