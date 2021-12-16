#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Graphics.hpp>
#include "DeltaTime.hpp"
#include "AnimatedSprite.hpp"
#include <unordered_map>
#include <functional>

enum PlayerAnimations
{
    GoRight,
    GoLeft,
    GoUp,
    GoDown,
    IdleRight,
    IdleLeft,
    IdleUp,
    IdleDown
};

class Player : public sf::Drawable
{
private:
    sf::Texture texture;
    std::unordered_map<PlayerAnimations, AnimatedSprite *> animations;
    sf::Vector2f center;
    sf::Vector2f position;
    sf::IntRect spriteRect;
    DeltaTime *dt;
    unsigned int fn = 0;
    bool initialized = false;
    bool idle = false;
    PlayerAnimations moveDirection;
    std::function<bool(sf::Vector2f)> collisionHandler;

    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const
    {
        sf::Vertex line[] = {
            sf::Vertex(sf::Vector2f(this->position.x, this->position.y), sf::Color::Red),
            sf::Vertex(sf::Vector2f(0, 0), sf::Color::Red)};

        this->animations.at(moveDirection)->nextFrame();
        target.draw(*this->animations.at(moveDirection), states);

        target.draw(line, 2, sf::Lines, states);
    }

    bool loadAnimatedSprite(std::string dirPath, PlayerAnimations direction);

public:
    void init(sf::Vector2f startPosition, sf::IntRect spriteRect, DeltaTime *dt);
    sf::Drawable *getSprite();
    void movePlayer(sf::Vector2f shift);
    sf::Vector2f getPosition()
    {
        return this->position;
    }

    void setAnimation(PlayerAnimations animation)
    {
        this->moveDirection = animation;
    }

    void bindCollision(std::function<bool(sf::Vector2f)> handler)
    {
        this->collisionHandler = handler;
    }
};

#endif // PLAYER_HPP