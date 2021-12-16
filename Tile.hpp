#ifndef TILE_HPP
#define TILE_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

class Tile : public sf::Drawable
{
private:
    float centerX;
    float centerY;
    sf::Vector2f centerPos;
    sf::Vector2f postion;
    sf::Sprite sprite;
    sf::IntRect spriteRect;
    float collisionRadius = 128.0f;

    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const
    {
        sf::Color color = this->walkable ? sf::Color::Green : sf::Color::Red;
        sf::Vertex line[] = {
            sf::Vertex(sf::Vector2f(this->postion.x, this->postion.y - this->spriteRect.height / 8), color),
            sf::Vertex(sf::Vector2f(this->postion.x + this->spriteRect.width / 2, this->postion.y), color),
            sf::Vertex(sf::Vector2f(this->postion.x + this->spriteRect.width / 2, this->postion.y), color),
            sf::Vertex(sf::Vector2f(this->postion.x, this->postion.y + this->spriteRect.height / 8), color),
            sf::Vertex(sf::Vector2f(this->postion.x, this->postion.y + this->spriteRect.height / 8), color),
            sf::Vertex(sf::Vector2f(this->postion.x - this->spriteRect.width / 2, this->postion.y), color),
            sf::Vertex(sf::Vector2f(this->postion.x - this->spriteRect.width / 2, this->postion.y), color),
            sf::Vertex(sf::Vector2f(this->postion.x, this->postion.y - this->spriteRect.height / 8), color),
        };

        sf::CircleShape shape(collisionRadius);
        shape.setFillColor(color);
        shape.setOrigin(collisionRadius, collisionRadius);
        shape.setPosition(this->postion);

        target.draw(this->sprite, states);
        target.draw(line, 8, sf::Lines, states);
        // target.draw(shape, states);
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

    bool collidePoint(sf::Vector2f point)
    {
        if (this->walkable)
            return false;

        float dist = this->distance(point.x, point.y, this->postion.x, this->postion.y);

        if (dist < collisionRadius)
        {
            return true;
        }

        return false;
    }

    float distance(int x1, int y1, int x2, int y2)
    {
        // Calculating distance
        return std::sqrt(std::pow(x2 - x1, 2) +
                         std::pow(y2 - y1, 2) * 1.0);
    }
};

#endif // TILE_HPP