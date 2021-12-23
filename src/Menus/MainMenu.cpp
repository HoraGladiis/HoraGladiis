#include "MainMenu.hpp"

MenuItem::MenuItem(std::string text, sf::Color color, sf::Color selectedColor, std::function<void(void)> callback)
{
    this->text = text;
    this->color = color;
    this->selectedColor = selectedColor;
    this->callback = callback;
}
MenuItem::~MenuItem() {}

MainMenu::MainMenu(std::string title)
{
    this->title = title;

    // TODO:

    itemIndex = 0;
}

MainMenu::~MainMenu()
{
}

void MainMenu::clearItems()
{
    this->items.clear();
}

void MainMenu::moveUp()
{
    this->itemIndex = this->mirror(this->itemIndex - 1);
}

void MainMenu::moveDown()
{
    this->itemIndex = this->mirror(this->itemIndex + 1);
}

void MainMenu::addItem(std::string text, sf::Color color, sf::Color selectedColor, std::function<void(void)> callback)
{
    this->items.push_back(MenuItem(text, color, selectedColor, callback));
}

void MainMenu::select()
{
    this->items.at(this->itemIndex).callback();
}