#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "../src/Tile.hpp"
#include <SFML/Graphics.hpp>

// позитивный
TEST_CASE("Testing collidePoint non walkable")
{
    Tile tile;
    sf::Texture texture;
    CHECK_NE(texture.create(10, 10), 0);
    tile.init(texture, sf::IntRect(0, 0, 10, 10));
    tile.setPosition(0.0, 0.0);
    tile.enable();
    tile.disableWalkable(); // тайл не доступен для перемещения

    CHECK(tile.collidePoint(sf::Vector2f(0.0, 0.0)));             // внутри collisionRadius
    CHECK(tile.collidePoint(sf::Vector2f(127.0, 0.0)));           // внутри collisionRadius
    CHECK(tile.collidePoint(sf::Vector2f(-40.0, 40.0)));          // внутри collisionRadius
    CHECK(tile.collidePoint(sf::Vector2f(-40.0, -40.0)));         // внутри collisionRadius
    CHECK(tile.collidePoint(sf::Vector2f(40.0, -40.0)));          // внутри collisionRadius
    CHECK(tile.collidePoint(sf::Vector2f(40.0, 40.0)));           // внутри collisionRadius
    CHECK_FALSE(tile.collidePoint(sf::Vector2f(128.0, 128.0)));   // вне collisionRadius
    CHECK_FALSE(tile.collidePoint(sf::Vector2f(-128.0, -128.0))); // вне collisionRadius
    CHECK_FALSE(tile.collidePoint(sf::Vector2f(128.0, -128.0)));  // вне collisionRadius
    CHECK_FALSE(tile.collidePoint(sf::Vector2f(-128.0, 128.0)));  // вне collisionRadius
}

// позитивный
TEST_CASE("Testing collidePoint walkable")
{
    Tile tile;
    sf::Texture texture;
    CHECK_NE(texture.create(10, 10), 0);
    tile.init(texture, sf::IntRect(0, 0, 10, 10));
    tile.setPosition(0.0, 0.0);
    tile.enable();
    tile.enableWalkable();                                        // тайл доступен для пермещения
    CHECK_FALSE(tile.collidePoint(sf::Vector2f(0.0, 0.0)));       // внутри collisionRadius
    CHECK_FALSE(tile.collidePoint(sf::Vector2f(127.0, 0.0)));     // внутри collisionRadius
    CHECK_FALSE(tile.collidePoint(sf::Vector2f(-40.0, 40.0)));    // внутри collisionRadius
    CHECK_FALSE(tile.collidePoint(sf::Vector2f(-40.0, -40.0)));   // внутри collisionRadius
    CHECK_FALSE(tile.collidePoint(sf::Vector2f(40.0, -40.0)));    // внутри collisionRadius
    CHECK_FALSE(tile.collidePoint(sf::Vector2f(40.0, 40.0)));     // внутри collisionRadius
    CHECK_FALSE(tile.collidePoint(sf::Vector2f(128.0, 128.0)));   // вне collisionRadius
    CHECK_FALSE(tile.collidePoint(sf::Vector2f(-128.0, -128.0))); // вне collisionRadius
    CHECK_FALSE(tile.collidePoint(sf::Vector2f(128.0, -128.0)));  // вне collisionRadius
    CHECK_FALSE(tile.collidePoint(sf::Vector2f(-128.0, 128.0)));  // вне collisionRadius
}
