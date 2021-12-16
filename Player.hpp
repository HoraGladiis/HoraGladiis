#include <SFML/Graphics.hpp>
#include "DeltaTime.hpp"
#include "AnimatedSprite.hpp"
#include <unordered_map>

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

    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const
    {
        this->animations.at(moveDirection)->nextFrame();
        target.draw(*this->animations.at(moveDirection), states);
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
    PlayerAnimations moveDirection;
};