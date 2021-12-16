#include "Game.hpp"

Game::Game(std::string title, sf::Vector2i initSize, int fpsLimit, bool enableVsync)
{
    std::cout << BOLDGREEN << "=== Create new game ===\n"
              << YELLOW;
    std::cout << "> Title:\t" << title << std::endl;
    std::cout << "> Resolution:\t" << initSize.x << "x" << initSize.y << std::endl;
    std::cout << "> Fps limit:\t" << fpsLimit << std::endl;
    std::cout << "> Vsync:\t" << (enableVsync ? "on" : "off") << std::endl;
    std::cout << "...\n";

    window = new sf::RenderWindow(sf::VideoMode(initSize.x, initSize.y), title);
    window->setFramerateLimit(fpsLimit);
    window->setVerticalSyncEnabled(enableVsync);

    std::cout << "> Assign new camera...\n";
    camera.setPosition(); // reset to 0, 0
    camera.assign(*window);
    std::cout << "> Done!\n\n"
              << RESET;
}

Game::~Game()
{
    free(window);

    for (auto &[key, val] : levels)
    {
        free(val);
    }
}

void Game::init()
{
    std::cout << BOLDGREEN << "=== Game init ===\n"
              << CYAN;
    std::cout << "> Init events...\n";

    std::function<void(sf::Event)> closeEvent = std::bind(&Game::closeGame, this, std::placeholders::_1);
    eventHandler.addHandler(sf::Event::Closed, closeEvent);
    std::function<void(sf::Event)> resizeEvent = std::bind(&Game::resizeWindow, this, std::placeholders::_1);
    eventHandler.addHandler(sf::Event::Resized, resizeEvent);

    // std::function<void(sf::Event)> keyEvent = std::bind(&Game::keyPressed, this, std::placeholders::_1);
    // eventHandler.addHandler(sf::Event::KeyPressed, keyEvent);

    std::cout << "> Done!\n\n"
              << RESET;

    std::cout << BLUE << "> Init tilesets...\n";

    Tileset *baseTilset = new Tileset("./assets/tiles/map/tileset.png", sf::Vector2i(512, 1024), 11);
    tilesets["base"] = baseTilset;

    std::cout << "> Done!\n\n"
              << RESET;

    std::cout << MAGENTA << "> Init levels...\n";

    GameLevel *startLevel = new GameLevel();
    startLevel->init("Start lvl", tilesets["base"]);
    levels["start"] = startLevel;

    std::cout << "> Done!\n\n"
              << RESET;
}

void Game::run()
{
    std::cout << BOLDGREEN << "=== Game run ===\n"
              << RESET;

    Player player;
    player.init(sf::Vector2f(0.0, 0.0), sf::IntRect(0, 0, 512, 1024), &deltaTime);

    int fps = 0;

    sf::Text dtime_text;
    sf::Text fps_text;
    sf::Font text_font;
    text_font.loadFromFile("./assets/fonts/OpenSans-Regular.ttf");
    dtime_text.setFont(text_font);
    dtime_text.setCharacterSize(25);
    dtime_text.setFillColor(sf::Color::Green);
    dtime_text.setPosition(sf::Vector2f(0.0, 0.0));

    fps_text.setFont(text_font);
    fps_text.setCharacterSize(25);
    fps_text.setFillColor(sf::Color::Green);
    fps_text.setPosition(sf::Vector2f(0.0, 0.0));

    sf::Texture texture;
    texture.loadFromFile("./assets/tiles/test_brick_floor.png");
    IsoTileMap map;
    // map.load(4, 4, texture, 512.0, 1024.0);

    std::vector<std::vector<int>> mapL = {{1, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 0}};

    map.loadTilset(4, 4, this->tilesets["base"], mapL);

    while (window->isOpen())
    {
        eventHandler.handleEvent(*window);

        float playerSpeed = 300.0;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            // shiftCamera(sf::Vector2f(500.0, 0.0));
            player.moveDirection = PlayerAnimations::GoRight;
            player.movePlayer(sf::Vector2f(cos(30 * M_PI / 180) * playerSpeed, sin(30 * M_PI / 180) * playerSpeed));
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            // shiftCamera(sf::Vector2f(-500.0, 0.0));
            player.moveDirection = PlayerAnimations::GoLeft;
            player.movePlayer(sf::Vector2f(cos(210 * M_PI / 180) * playerSpeed, sin(210 * M_PI / 180) * playerSpeed));
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            // shiftCamera(sf::Vector2f(0.0, -500.0));
            player.moveDirection = PlayerAnimations::GoUp;
            player.movePlayer(sf::Vector2f(cos(330 * M_PI / 180) * playerSpeed, sin(330 * M_PI / 180) * playerSpeed));
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            // shiftCamera(sf::Vector2f(0.0, 500.0));
            player.moveDirection = PlayerAnimations::GoDown;
            player.movePlayer(sf::Vector2f(cos(150 * M_PI / 180) * playerSpeed, sin(150 * M_PI / 180) * playerSpeed));
        }

        camera.setPosition(player.getPosition());

        window->clear();

        window->draw(*levels["start"]);
        window->draw(player);

        fps_text.setString("FPS: " + std::to_string(fps));
        fps_text.setPosition(window->mapPixelToCoords(sf::Vector2i(5, 5)));
        window->draw(fps_text);

        // dtime_text.setString("Delta time: " + std::to_string((int)(dtime * 1000)));
        // dtime_text.setPosition(window->mapPixelToCoords(sf::Vector2i(5, 5)));
        // window->draw(dtime_text);

        window->display();

        dtime = deltaTime.loop();
        fps = (int)std::round(1.0f / dtime);
    }

    std::cout << BOLDRED << "=== Game exit ===" << RESET << std::endl;
}