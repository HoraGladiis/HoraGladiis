#include <SFML/Graphics.hpp>
#include <vector>
#include <set>
#include <filesystem>
#include <iostream>

class AnimatedSprite : public sf::Sprite
{
private:
    std::vector<sf::Texture *> textures;
    std::size_t frameCount;
    uint frameIndex = 0;

public:
    bool debug = false;
    bool loadFromFolder(std::string folderPath);
    sf::Texture *getFrameTexture(std::size_t index);
    sf::Texture *getFrameTexture();

    void nextFrame();
    void goToFrame(uint index);
};
