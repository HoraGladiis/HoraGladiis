#include "AnimatedSprite.hpp"

namespace fs = std::filesystem;

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

        sf::Texture *texture = new sf::Texture();
        if (!texture->loadFromFile(filename))
        {
            std::cerr << "Can't load file: " << filename << std::endl;
            return false;
        }

        this->textures.push_back(texture);
    }

    this->frameCount = this->textures.size();

    this->goToFrame(0);

    return true;
}

sf::Texture *AnimatedSprite::getFrameTexture(std::size_t index)
{
    std::size_t boundedIndex = index % this->frameCount;

    try
    {
        return this->textures.at(boundedIndex);
    }
    catch (std::out_of_range const &exc)
    {
        std::cerr << "Animated sprite error: " << exc.what() << std::endl;
    }

    return nullptr;
}

sf::Texture *AnimatedSprite::getFrameTexture()
{
    return this->getFrameTexture(this->frameIndex);
}

void AnimatedSprite::nextFrame()
{
    if (this->frameCount == 0)
        return;

    this->frameIndex = (this->frameIndex + 1) % this->frameCount;
    this->setTexture(*this->getFrameTexture());
}

void AnimatedSprite::goToFrame(uint index)
{
    if (this->frameCount == 0)
        return;

    this->frameIndex = index % this->frameCount;
    this->setTexture(*this->getFrameTexture());
}