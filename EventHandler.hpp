#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <functional>
#include <vector>

class EventHandler
{
private:
    std::unordered_map<sf::Event::EventType, std::vector<std::function<void(sf::Event)>>> _handlers;

public:
    EventHandler();
    ~EventHandler();
    void handleEvent(sf::RenderWindow &window);
    void addHandler(sf::Event::EventType eventType, std::function<void(sf::Event)> handler);
};
