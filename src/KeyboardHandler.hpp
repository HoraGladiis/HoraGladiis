#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <functional>
#include <vector>

class KeyboardHandler
{
private:
    std::unordered_map<sf::Keyboard::Key, std::vector<std::function<void(sf::Keyboard::Key)>>> _handlers;

public:
    KeyboardHandler();
    ~KeyboardHandler();
    void handleKeyboard();
    void addHandler(sf::Keyboard::Key key, std::function<void(sf::Keyboard::Key)> handler);
};
