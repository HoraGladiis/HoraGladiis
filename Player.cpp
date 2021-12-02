#include "Player.hpp"

Player::Player(sf::Vector2f startPosition, std::string spritePath, sf::IntRect spriteRect, DeltaTime *dt)
{
    this->position = startPosition;

    this->spriteRect = spriteRect;

    this->center.x = this->spriteRect.width / 2.0;
    this->center.y = this->spriteRect.height / 2.0;

    texture.loadFromFile(spritePath);

    this->sprite = new sf::Sprite(this->texture, this->spriteRect);

    this->sprite->setOrigin(this->center);

    this->sprite->setPosition(startPosition);

    this->dt = dt;

    AnimatedSprite ass;
    ass.debug = true;
    ass.loadFromFolder("./assets/tiles/tmp/");
}

Player::~Player()
{
}

sf::Sprite *Player::getSprite()
{
    return this->sprite;
}

void Player::move(sf::Vector2f shift)
{
    this->position += shift * dt->get();
    this->sprite->setPosition(this->position);
}
