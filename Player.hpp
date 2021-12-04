#include <SFML/Graphics.hpp>
#include "DeltaTime.hpp"
#include "AnimatedSprite.hpp"

class Player : public sf::Drawable
{
private:
    sf::Texture texture;
    AnimatedSprite *animatedSprite;
    sf::Vector2f center;
    sf::Vector2f position;
    sf::IntRect spriteRect;
    DeltaTime *dt;
    unsigned int fn = 0;
    bool initialized = false;

    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const
    {
        this->animatedSprite->nextFrame();
        target.draw(*this->animatedSprite, states);
    }

public:
    void init(sf::Vector2f startPosition, sf::IntRect spriteRect, DeltaTime *dt);
    sf::Drawable *getSprite();
    void movePlayer(sf::Vector2f shift);
    sf::Vector2f getPosition()
    {
        return this->position;
    }
};
