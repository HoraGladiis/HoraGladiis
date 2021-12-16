#include "DeltaTime.hpp"

DeltaTime::DeltaTime()
{
}

DeltaTime::~DeltaTime()
{
}

float DeltaTime::loop()
{
    deltaTime = deltaClock.restart();
    current = deltaTime.asSeconds();
    return current;
}

float DeltaTime::get()
{
    return current;
}

sf::Time DeltaTime::getSfTime()
{
    return deltaClock.getElapsedTime();
}