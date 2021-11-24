#include <SFML/Graphics.hpp>

class Character
{
private:
    sf::Texture *frames;
    sf::IntRect frameRect;
    sf::Sprite *currentSprite;
    int framesCount;
    sf::Vector2f center;

    sf::IntRect getRectForFrame(unsigned int textureW, unsigned int textureH, unsigned int frameW, unsigned int frameH, unsigned int frameNumber);

public:
    Character(std::string framesPath, sf::Vector2i frameSize, int framesCount);
    ~Character();

    sf::Sprite *getCurrentFrame(int n);
    void setPosition(sf::Vector2f pos);
    void move(sf::Vector2f shift);
};
