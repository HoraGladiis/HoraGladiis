#include <SFML/Graphics.hpp>
#include <iostream>
#include <functional>
#include <cmath>
#include <map>
#include "Camera.hpp"
#include "Character.hpp"
#include "EventHandler.hpp"
#include "DeltaTime.hpp"
#include "GameLevel.hpp"
#include "Tileset.hpp"
#include "Player.hpp"
#include "misc.hpp"

class Game
{
private:
    sf::RenderWindow *window;
    Camera camera;
    EventHandler eventHandler;
    DeltaTime deltaTime;
    float dtime = 0;

    std::map<std::string, Tileset *> tilesets;
    std::map<std::string, GameLevel *> levels;

public:
    Game(std::string title, sf::Vector2i initSize, int fpsLimit, bool enableVsync);
    ~Game();

    void init();
    void run();

    void closeGame(sf::Event event)
    {
        UNUSED(event);
        window->close();
    }

    void resizeWindow(sf::Event event)
    {
        camera.resizeCamera(event);
    }

    void keyPressed(sf::Event event)
    {
        const float camShift = 1000.0;
        sf::Vector2f cameraOffset(0.0, 0.0);

        if (event.key.code == sf::Keyboard::Right || event.key.code == sf::Keyboard::D)
        {
            cameraOffset.x += camShift * dtime;
        }
        if (event.key.code == sf::Keyboard::Left || event.key.code == sf::Keyboard::A)
        {
            cameraOffset.x -= camShift * dtime;
        }
        if (event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::W)
        {
            cameraOffset.y -= camShift * dtime;
        }
        if (event.key.code == sf::Keyboard::Down || event.key.code == sf::Keyboard::S)
        {
            cameraOffset.y += camShift * dtime;
        }

        camera.move(cameraOffset);
    }

    void shiftCamera(sf::Vector2f cameraOffset)
    {
        cameraOffset *= dtime;
        camera.move(cameraOffset);
    }
};
