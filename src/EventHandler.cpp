#include "EventHandler.hpp"
#include <iostream>

EventHandler::EventHandler()
{
}

EventHandler::~EventHandler()
{
}

void EventHandler::handleEvent(sf::RenderWindow &window)
{
    sf::Event event;

    while (window.pollEvent(event))
    {
        for (std::function<void(sf::Event)> handler : this->_handlers[event.type])
        {
            handler(event);
        }
    }
}

void EventHandler::addHandler(sf::Event::EventType eventType, std::function<void(sf::Event)> handler)
{
    if (!handler)
        return;

    if (this->_handlers.find(eventType) == this->_handlers.end())
        this->_handlers[eventType] = std::vector<std::function<void(sf::Event)>>();

    this->_handlers[eventType].push_back(handler);

    std::cout << "New handler with type = " << eventType << std::endl;
}
