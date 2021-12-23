#include <SFML/Graphics.hpp>
#include <vector>

class MenuItem
{
public:
    std::string text;
    sf::Color color;
    sf::Color selectedColor;
    MenuItem(std::string text, sf::Color color, sf::Color selectedColor)
    {
        this->text = text;
        this->color = color;
        this->selectedColor = selectedColor;
    }
    ~MenuItem();
};

class MainMenu
{
private:
    std::vector<MenuItem> items;
    std::string title;
    uint itemIndex;

public:
    MainMenu(std::string title);
    ~MainMenu();
    void moveUp();
    void modeDown();
    void select();
    void clearItems();
    void addItem(std::string text, sf::Color color, sf::Color selectedColor);
};

MainMenu::MainMenu(std::string title)
{
    this->title = title;

    // TODO:

    itemIndex = 0;
}

MainMenu::~MainMenu()
{
}
