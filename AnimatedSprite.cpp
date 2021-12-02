#include "AnimatedSprite.hpp"

namespace fs = std::filesystem;

AnimatedSprite::AnimatedSprite()
{
}

AnimatedSprite::~AnimatedSprite()
{
}

bool AnimatedSprite::loadFromFolder(std::string folderPath)
{
    std::vector<fs::path> filesInDirectory;

    if (debug)
        std::cout << "Iterate dir: " << folderPath << std::endl;

    std::copy(fs::directory_iterator(folderPath),
              fs::directory_iterator(),
              std::back_inserter(filesInDirectory));

    if (debug)
        std::cout << "Sort dirs by name..."
                  << std::endl;

    std::sort(filesInDirectory.begin(), filesInDirectory.end());

    if (debug)
        std::cout << "Texture files: "
                  << std::endl;
    for (const fs::path &filename : filesInDirectory)
    {
        if (debug)
            std::cout << filename.filename() << "\t";

        sf::Texture texture;
        if (!texture.loadFromFile(filename))
        {
            std::cerr << "Can't load file: " << filename << std::endl;
            return false;
        }

        this->textures[filename] = texture;
    }

    if (debug)
    {
        std::cout << std::endl
                  << std::endl
                  << "Creating sprites:"
                  << std::endl;
    }

    for (const auto &[key, value] : this->textures)
    {
        if (debug)
            std::cout << key.filename() << "\t";

        sf::Sprite sprite;
        sprite.setTexture(value);
    }

    if (debug)
        std::cout << std::endl
                  << std::endl;

    return true;
}