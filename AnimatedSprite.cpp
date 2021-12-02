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
    std::set<fs::path> sortedPaths;

    for (const fs::directory_entry &entry : fs::directory_iterator(folderPath))
    {
        fs::path path = entry.path();

        sortedPaths.insert(path);
    }

    // for (const fs::path)
    //     return true;
}