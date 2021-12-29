#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include <functional>
#include <cmath>
#include <map>
#include "Camera.hpp"
#include "Character.hpp"
#include "EventHandler.hpp"
#include "KeyboardHandler.hpp"
#include "DeltaTime.hpp"
#include "GameLevel.hpp"
#include "Tileset.hpp"
#include "Player.hpp"
#include "Menus/MainMenu.hpp"
#include "misc.hpp"
#include <functional>
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>

#define THEME_CONFIG_FILE "./assets/kenney-5/kenney.style"

enum class GameExitStatus
{
    NewGame,
    JustExit,
    Default
};

class Game
{
private:
    sf::RenderWindow *window;
    Camera camera;
    EventHandler eventHandler;
    KeyboardHandler keyboardHandler;
    DeltaTime deltaTime;
    float dtime = 0;

    std::map<std::string, Tileset *> tilesets;
    std::map<std::string, GameLevel *> levels;

    Player *_player;
    MainMenu *_mainMenu;

    bool gameRunning = false;
    bool firstRun = true;

public:
    Game(std::string title, sf::Vector2i initSize, int fpsLimit, bool enableVsync);
    ~Game();

    GameExitStatus exitStatus = GameExitStatus::Default;

    tgui::Gui *gui;

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

    void newGame()
    {
        if (this->firstRun)
        {
            this->firstRun = false;
            this->gameRunning = true;
            return;
        }

        this->exitStatus = GameExitStatus::NewGame;
        window->clear(sf::Color(111, 168, 54));
        window->display();
        window->close();
    }

    void settingsMenu()
    {
        std::cout << RED << "Не реализовано!!!" << RESET << std::endl;
    }

    void continueBtn()
    {
        if (this->firstRun)
        {
            std::cout << RED << "Игра не начата" << RESET << std::endl;
            return;
        }
        gameRunning = true;
    }

    void exitBtn()
    {
        this->exitStatus = GameExitStatus::JustExit;
        window->close();
    }

    void exitToMenu(sf::Keyboard::Key k)
    {
        UNUSED(k);
        this->gameRunning = false;
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

    bool collidePoint(sf::Vector2f point)
    {
        // for (const std::pair<const std::string, const GameLevel *> &l : levels)
        // {

        // }

        return this->levels["start"]->collidePoint(point);
    }

    void movePlayer(sf::Keyboard::Key k)
    {
        float playerSpeed = 300.0;

        switch (k)
        {
        case sf::Keyboard::D:
        case sf::Keyboard::Right:
            this->_player->setAnimation(PlayerAnimations::GoRight);
            this->_player->movePlayer(sf::Vector2f(cos(30 * M_PI / 180) * playerSpeed, sin(30 * M_PI / 180) * playerSpeed));
            break;

        case sf::Keyboard::A:
        case sf::Keyboard::Left:
            this->_player->setAnimation(PlayerAnimations::GoLeft);
            this->_player->movePlayer(sf::Vector2f(cos(210 * M_PI / 180) * playerSpeed, sin(210 * M_PI / 180) * playerSpeed));
            break;

        case sf::Keyboard::W:
        case sf::Keyboard::Up:
            this->_player->setAnimation(PlayerAnimations::GoUp);
            this->_player->movePlayer(sf::Vector2f(cos(330 * M_PI / 180) * playerSpeed, sin(330 * M_PI / 180) * playerSpeed));
            break;

        case sf::Keyboard::S:
        case sf::Keyboard::Down:
            this->_player->setAnimation(PlayerAnimations::GoDown);
            this->_player->movePlayer(sf::Vector2f(cos(150 * M_PI / 180) * playerSpeed, sin(150 * M_PI / 180) * playerSpeed));
            break;

        default:
            this->_player->movePlayer(sf::Vector2f(0, 0));
        }
    }

    // void openMainMenu(sf::Keyboard::Key k)
    // {
    // }
};

#endif // GAME_HPP