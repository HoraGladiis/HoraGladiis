#ifndef DELTATIME_HPP
#define DELTATIME_HPP

#include <SFML/Graphics.hpp>

class DeltaTime
{
private:
    sf::Clock deltaClock;
    sf::Time deltaTime;
    float current = 0.0;

public:
    DeltaTime();
    ~DeltaTime();
    float loop();
    float get();
    sf::Time getSfTime();
};

#endif // DELTATIME_HPP
