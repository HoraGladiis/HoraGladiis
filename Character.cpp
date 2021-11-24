#include "Character.hpp"

sf::IntRect Character::getRectForFrame(unsigned int textureW, unsigned int textureH, unsigned int frameW, unsigned int frameH, unsigned int frameNumber)
{
    unsigned int colCount = textureW / frameW;
    unsigned int rowCount = textureH / frameH;

    int left = frameW * (frameNumber % colCount);
    int top = frameH * ((frameNumber / colCount) % rowCount);

    return sf::IntRect(left, top, frameW, frameH);
}

sf::Sprite *Character::getCurrentFrame(int n)
{
    sf::Vector2u s = this->frames->getSize();
    sf::IntRect r = getRectForFrame(s.x, s.y, 512, 1024, n);

    this->currentSprite->setTextureRect(r);
    return this->currentSprite;
}

Character::Character(std::string framesPath, sf::Vector2i frameSize, int framesCount)
{
    this->frames = new sf::Texture();
    this->frames->loadFromFile(framesPath);

    this->frameRect = sf::IntRect(sf::Vector2i(0, 0), frameSize);

    center.x = this->frameRect.width / 2.0;
    center.y = this->frameRect.height / 2.0;

    this->currentSprite = new sf::Sprite(*this->frames, this->frameRect);
    this->framesCount = framesCount;

    currentSprite->setOrigin(this->center);

    this->frameRect = sf::IntRect(0, 0, 512, 1024);
}

Character::~Character()
{
    free(this->frames);
    // free(this->frameRect);
    free(this->currentSprite);
}

void Character::setPosition(sf::Vector2f pos)
{
    this->currentSprite->setPosition(pos);
}

void Character::move(sf::Vector2f shift)
{
    this->currentSprite->move(shift);
}