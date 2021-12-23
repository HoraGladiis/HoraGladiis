#include "KeyboardHandler.hpp"
#include <iostream>

KeyboardHandler::KeyboardHandler()
{
}

KeyboardHandler::~KeyboardHandler()
{
}

void KeyboardHandler::handleKeyboard()
{
    for (std::pair<sf::Keyboard::Key, std::vector<std::function<void(sf::Keyboard::Key)>>> part : this->_handlers)
    {
        if (sf::Keyboard::isKeyPressed(part.first))
        {
            for (std::function<void(sf::Keyboard::Key)> handler : part.second)
            {
                handler(part.first);
            }
        }
    }
}

void KeyboardHandler::addHandler(sf::Keyboard::Key key, std::function<void(sf::Keyboard::Key)> handler)
{
    if (!handler)
        return;

    if (this->_handlers.find(key) == this->_handlers.end())
        this->_handlers[key] = std::vector<std::function<void(sf::Keyboard::Key)>>();

    this->_handlers[key].push_back(handler);

    std::cout << "New handler with type = " << key << std::endl;
}
