#include "Tile.hpp"

void Tile::init(sf::Texture &texture, sf::IntRect rect)
{
    this->setTexture(texture);
    this->setTextureRect(rect);
    center.x = rect.width / 2.0;
    center.y = rect.height / 2.0;
    this->setOrigin(center);

    this->enabled = true;
}

sf::Vector2f Tile::getCenter()
{
    sf::Vector2f pos = this->getPosition();
    return pos;
}