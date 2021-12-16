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

    this->loadAnimatedSprite("./assets/tiles/player/idelse/", PlayerAnimations::IdleRight);
    this->loadAnimatedSprite("./assets/tiles/player/idelne/", PlayerAnimations::IdleUp);
    this->loadAnimatedSprite("./assets/tiles/player/idelwn/", PlayerAnimations::IdleLeft);
    this->loadAnimatedSprite("./assets/tiles/player/idelws/", PlayerAnimations::IdleDown);

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
    // FIXME: тестовый idle для анимаций
    if (shift.x == 0 && shift.y == 0)
    {
        if (this->moveDirection == PlayerAnimations::GoLeft)
        {
            this->setAnimation(PlayerAnimations::IdleLeft);
        }
        else if (this->moveDirection == PlayerAnimations::GoRight)
        {
            this->moveDirection = PlayerAnimations::IdleRight;
        }
        if (this->moveDirection == PlayerAnimations::GoUp)
        {
            this->moveDirection = PlayerAnimations::IdleUp;
        }
        else if (this->moveDirection == PlayerAnimations::GoDown)
        {
            this->moveDirection = PlayerAnimations::IdleDown;
        }
    }

    this->position += shift * dt->get();
    this->animations[moveDirection]->setPosition(this->position);
}
