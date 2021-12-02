#include <SFML/Graphics.hpp>
#include "DeltaTime.hpp"
#include "AnimatedSprite.hpp"

class Player
{
private:
    sf::Texture texture;
    sf::Sprite *sprite;
    sf::Vector2f center;
    sf::Vector2f position;
    sf::IntRect spriteRect;
    DeltaTime *dt;

public:
    Player(sf::Vector2f startPosition, std::string spritePath, sf::IntRect spriteRect, DeltaTime *dt);
    ~Player();
    sf::Sprite *getSprite();
    void move(sf::Vector2f shift);
    sf::Vector2f getPosition()
    {
        return this->position;
    }
};
