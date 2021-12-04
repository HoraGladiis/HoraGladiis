#include "Player.hpp"

void Player::init(sf::Vector2f startPosition, sf::IntRect spriteRect, DeltaTime *dt)
{
    this->position = startPosition;
    this->spriteRect = spriteRect;
    this->center.x = this->spriteRect.width / 2.0;
    this->center.y = this->spriteRect.height / 2.0;

    this->dt = dt;

    this->animatedSprite = new AnimatedSprite();
    this->animatedSprite->debug = true;
    this->animatedSprite->setOrigin(this->center);
    this->animatedSprite->setPosition(startPosition);

    bool ok = this->animatedSprite->loadFromFolder("./assets/tiles/tmp/");
    std::cout << std::endl;

    if (ok)
    {
        std::cout << "Animated sprite: ok" << std::endl;
    }
    else
    {
        std::cerr << "Animated sprite: error" << std::endl;
    }

    this->initialized = true;
}

sf::Drawable *Player::getSprite()
{
    // sf::Texture *t = this->animatedSprite->getFrameTexture(fn++);
    // this->sprite->setTexture(*t);
    this->animatedSprite->nextFrame();
    return this->animatedSprite;
}

void Player::movePlayer(sf::Vector2f shift)
{
    this->position += shift * dt->get();
    this->animatedSprite->setPosition(this->position);
}
