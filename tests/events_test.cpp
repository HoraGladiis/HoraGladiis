#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "../src/EventHandler.hpp"
#include <SFML/Graphics.hpp>

class EventChecker
{
private:
    int value;
    int targetValue;

public:
    EventChecker(int target);
    ~EventChecker();

    void resetValue()
    {
        this->value = 0;
    }

    void dummyCallback(sf::Event event)
    {
        this->value = this->targetValue;
    }

    int getValue()
    {
        return this->value;
    }
};

// переопределяем pollEvent
bool sf::Window::pollEvent(sf::Event &event)
{
    if (event.type == sf::Event::Closed)
    {
        return false;
    }

    event.type = sf::Event::Closed;
    return true;
}

EventChecker::EventChecker(int target)
{
    this->value = 0;
    this->targetValue = target;
}
EventChecker::~EventChecker()
{
}

// позитивный
TEST_CASE("Testing EventHandler one callback")
{
    int target = 42;
    EventHandler handler;
    EventChecker checker(target);
    sf::RenderWindow fakeWindow;

    checker.resetValue();

    std::function<void(sf::Event)> testEvent = std::bind(&EventChecker::dummyCallback, &checker, std::placeholders::_1);
    handler.addHandler(sf::Event::Closed, testEvent);

    handler.handleEvent(fakeWindow);

    CHECK(checker.getValue() == target);
}

// позитивный
TEST_CASE("Testing EventHandler multiple callbacks")
{
    int target = 42;
    int target2 = 4242;

    EventHandler handler;
    EventChecker checker(target);
    EventChecker checker2(target2);
    sf::RenderWindow fakeWindow;

    checker.resetValue();

    std::function<void(sf::Event)> testEvent = std::bind(&EventChecker::dummyCallback, &checker, std::placeholders::_1);
    handler.addHandler(sf::Event::Closed, testEvent);
    std::function<void(sf::Event)> testEvent2 = std::bind(&EventChecker::dummyCallback, &checker2, std::placeholders::_1);
    handler.addHandler(sf::Event::Closed, testEvent2);

    handler.handleEvent(fakeWindow);

    CHECK(checker.getValue() == target);
    CHECK(checker2.getValue() == target2);
}

// негативный
TEST_CASE("Testing EventHandler null callback")
{
    EventHandler handler;
    sf::RenderWindow fakeWindow;

    handler.addHandler(sf::Event::Closed, nullptr);

    handler.handleEvent(fakeWindow);

    CHECK(true);
}
