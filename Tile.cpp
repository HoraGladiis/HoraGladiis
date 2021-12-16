#include "Tile.hpp"

void Tile::init(sf::Texture &texture, sf::IntRect rect)
{
    this->spriteRect = rect;
    this->sprite.setTexture(texture);
    this->sprite.setTextureRect(rect);
    centerPos.x = rect.width / 2.0;
    centerPos.y = rect.height / 2.0;
    this->sprite.setOrigin(centerPos);

    this->enabled = true;
}

sf::Vector2f Tile::getCenter()
{
    sf::Vector2f pos = this->sprite.getPosition();
    return pos;
}