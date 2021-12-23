#include "MainMenu.hpp"

MenuItem::MenuItem(std::string text, sf::Color color, sf::Color selectedColor, std::function<void(void)> callback)
{
    this->text = text;
    this->color = color;
    this->selectedColor = selectedColor;
    this->callback = callback;

    this->sfText.setString(this->text);
    this->sfText.setCharacterSize(24);
    this->sfText.setFillColor(this->color);
}
MenuItem::~MenuItem() {}

sf::Text MenuItem::getDrawable()
{
    return this->sfText;
}

MainMenu::MainMenu(std::string title)
{
    this->title = title;

    this->sfText.setString(this->title);
    this->sfText.setCharacterSize(24);
    this->sfText.setFillColor(sf::Color::White);
    this->sfText.setStyle(sf::Text::Bold | sf::Text::Underlined);

    itemIndex = 0;
}

sf::Text MainMenu::getDrawable()
{
    return this->sfText;
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