#ifndef TILE_HPP
#define TILE_HPP

#include <SFML/Graphics.hpp>
#include <iostream>

class Tile : public sf::Drawable
{
private:
    float centerX;
    float centerY;
    sf::Vector2f centerPos;
    sf::Vector2f postion;
    sf::Sprite sprite;
    sf::IntRect spriteRect;

    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const
    {
        sf::CircleShape shape(20);

        sf::Vertex line[] = {
            sf::Vertex(sf::Vector2f(this->postion.x, this->postion.y - this->spriteRect.height / 8), sf::Color::Green),
            sf::Vertex(sf::Vector2f(this->postion.x + this->spriteRect.width / 2, this->postion.y), sf::Color::Green),
            sf::Vertex(sf::Vector2f(this->postion.x + this->spriteRect.width / 2, this->postion.y), sf::Color::Green),
            sf::Vertex(sf::Vector2f(this->postion.x, this->postion.y + this->spriteRect.height / 8), sf::Color::Green),
            sf::Vertex(sf::Vector2f(this->postion.x, this->postion.y + this->spriteRect.height / 8), sf::Color::Green),
            sf::Vertex(sf::Vector2f(this->postion.x - this->spriteRect.width / 2, this->postion.y), sf::Color::Green),
            sf::Vertex(sf::Vector2f(this->postion.x - this->spriteRect.width / 2, this->postion.y), sf::Color::Green),
            sf::Vertex(sf::Vector2f(this->postion.x, this->postion.y - this->spriteRect.height / 8), sf::Color::Green),
        };

        target.draw(this->sprite, states);
        target.draw(line, 8, sf::Lines, states);
    }

public:
    void
    init(sf::Texture &texture, sf::IntRect rect);
    sf::Vector2f getCenter();
    bool enabled = false;
    bool walkable = true;

    Tile()
    {
    }

    ~Tile()
    {
    }

    void enable()
    {
        enabled = true;
    }

    void disable()
    {
        enabled = false;
    }

    void enableWalkable()
    {
        walkable = true;
    }

    void disableWalkable()
    {
        walkable = false;
    }

    void setPosition(float x, float y)
    {
        this->postion = sf::Vector2f(x, y);
        this->sprite.setPosition(this->postion);
    }

    sf::ConvexShape drawDebug()
    {
        sf::ConvexShape shape;
        shape.setPointCount(4);
        sf::FloatRect bounds = this->sprite.getGlobalBounds();

        shape.setPoint(0, sf::Vector2f(bounds.left, 0));
        shape.setPoint(1, sf::Vector2f(0, bounds.top));
        shape.setPoint(2, sf::Vector2f(bounds.width, 0));
        shape.setPoint(3, sf::Vector2f(0, bounds.height));

        return shape;
    }
};

#endif // TILE_HPP