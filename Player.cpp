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

    AnimatedSprite as;
    as.debug = true;
    bool ok = as.loadFromFolder("./assets/tiles/tmp/");

    if (ok)
    {
        std::cout << "Animated sprite: ok" << std::endl;
    }
    else
    {
        std::cerr << "Animated sprite: error" << std::endl;
    }
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
