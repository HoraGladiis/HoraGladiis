#include <SFML/Graphics.hpp>
#include <vector>
#include <set>
#include <filesystem>
#include <iostream>

class AnimatedSprite
{
private:
    std::vector<sf::Texture> frames;

public:
    AnimatedSprite();
    ~AnimatedSprite();
    bool debug = false;
    bool loadFromFolder(std::string folderPath);
};
