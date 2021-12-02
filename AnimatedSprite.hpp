#include <SFML/Graphics.hpp>
#include <vector>
#include <set>
#include <filesystem>
#include <iostream>

class AnimatedSprite
{
private:
    std::map<std::filesystem::path, sf::Texture> textures;
    std::map<std::filesystem::path, sf::Sprite> frames;

public:
    AnimatedSprite();
    ~AnimatedSprite();
    bool debug = false;
    bool loadFromFolder(std::string folderPath);
};
