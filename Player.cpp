#include "Player.hpp"

void Player::init(sf::Vector2f startPosition, sf::IntRect spriteRect, DeltaTime *dt)
{
    this->position = startPosition;
    this->spriteRect = spriteRect;
    this->center.x = this->spriteRect.width / 2.0;
    this->center.y = this->spriteRect.height / 2.0;

    this->dt = dt;

    this->loadAnimatedSprite("./assets/tiles/player/SE/", PlayerAnimations::GoRight);
    this->loadAnimatedSprite("./assets/tiles/player/NE/", PlayerAnimations::GoUp);
    this->loadAnimatedSprite("./assets/tiles/player/WN/", PlayerAnimations::GoLeft);
    this->loadAnimatedSprite("./assets/tiles/player/WS/", PlayerAnimations::GoDown);

    this->moveDirection = PlayerAnimations::GoRight;

    this->initialized = true;
}

bool Player::loadAnimatedSprite(std::string dirPath, PlayerAnimations direction)
{
    this->animations[direction] = new AnimatedSprite();
    this->animations[direction]->debug = true;
    this->animations[direction]->setOrigin(this->center);
    this->animations[direction]->setPosition(this->position);
    this->animations[direction]->loadFromFolder(dirPath);

    return true;
}

sf::Drawable *Player::getSprite()
{
    // sf::Texture *t = this->animatedSprite->getFrameTexture(fn++);
    // this->sprite->setTexture(*t);
    this->animations.at(moveDirection)->nextFrame();
    return this->animations.at(moveDirection);
}

void Player::movePlayer(sf::Vector2f shift)
{
    this->position += shift * dt->get();
    this->animations[moveDirection]->setPosition(this->position);
}
