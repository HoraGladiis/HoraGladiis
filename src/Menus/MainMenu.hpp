#include <SFML/Graphics.hpp>
#include <vector>

class MenuItem
{
public:
    std::string text;
    sf::Color color;
    sf::Color selectedColor;
    std::function<void(void)> callback;

    MenuItem(std::string text, sf::Color color, sf::Color selectedColor, std::function<void(void)> callback);
    ~MenuItem();
};

class MainMenu
{
private:
    std::vector<MenuItem> items;
    std::string title;
    int itemIndex;

    // Функция модуля
    int mirror(int i)
    {
        int itemCount = items.size();
        return (itemCount + (i % itemCount)) % itemCount;
    }

public:
    MainMenu(std::string title);
    ~MainMenu();
    void moveUp();
    void moveDown();
    void select();
    void clearItems();
    void addItem(std::string text, sf::Color color, sf::Color selectedColor, std::function<void(void)> callback);
};
