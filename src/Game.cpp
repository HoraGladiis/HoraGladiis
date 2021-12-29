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

    std::function<void(sf::Keyboard::Key)> movePlayerCmd = std::bind(&Game::movePlayer, this, std::placeholders::_1);
    keyboardHandler.addHandler(sf::Keyboard::Key::W, movePlayerCmd);
    keyboardHandler.addHandler(sf::Keyboard::Key::A, movePlayerCmd);
    keyboardHandler.addHandler(sf::Keyboard::Key::S, movePlayerCmd);
    keyboardHandler.addHandler(sf::Keyboard::Key::D, movePlayerCmd);
    keyboardHandler.addHandler(sf::Keyboard::Key::Up, movePlayerCmd);
    keyboardHandler.addHandler(sf::Keyboard::Key::Left, movePlayerCmd);
    keyboardHandler.addHandler(sf::Keyboard::Key::Down, movePlayerCmd);
    keyboardHandler.addHandler(sf::Keyboard::Key::Right, movePlayerCmd);

    std::function<void(sf::Keyboard::Key)> exitToMenuEvent = std::bind(&Game::exitToMenu, this, std::placeholders::_1);
    keyboardHandler.addHandler(sf::Keyboard::Key::Escape, exitToMenuEvent);

    // std::function<void(sf::Keyboard::Key)> movePlayerCmd = std::bind(&Game::openMainMenu, this, std::placeholders::_1);
    // keyboardHandler.addHandler(sf::Keyboard::Key::W, movePlayerCmd);

    // std::function<void(sf::Event)> keyEvent = std::bind(&Game::keyPressed, this, std::placeholders::_1);
    // eventHandler.addHandler(sf::Event::KeyPressed, keyEvent);

    std::cout
        << "> Done!\n\n"
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

    std::cout << GREEN << "Create Player...\n";
    this->_player = new Player();
    std::cout << "> Done!\n\n"
              << RESET;

    this->_mainMenu = new MainMenu("Главное меню");
    this->gui = new tgui::Gui(*this->window);
    this->inventoryGui = new tgui::Gui(*this->window);

    this->eventHandler.setGui(this->gui);
    this->eventHandler.setInvGui(this->inventoryGui);

    auto startBtn = tgui::Button::create("Новая игра");
    startBtn->setOrigin(sf::Vector2f(0.5, 0.5));
    startBtn->setSize({400, 100});
    startBtn->setPosition({"50%", 100});
    startBtn->setTextSize(50);
    startBtn->onClick(&Game::newGame, this);

    auto continueBtn = tgui::Button::create("Продолжить");
    continueBtn->setOrigin(sf::Vector2f(0.5, 0.5));
    continueBtn->setSize({400, 100});
    continueBtn->setPosition({"50%", 220});
    continueBtn->setTextSize(50);
    continueBtn->onClick(&Game::continueBtn, this);

    auto settingsBtn = tgui::Button::create("Настройки");
    settingsBtn->setOrigin(sf::Vector2f(0.5, 0.5));
    settingsBtn->setSize({400, 100});
    settingsBtn->setPosition({"50%", 340});
    settingsBtn->setTextSize(50);
    settingsBtn->onClick(&Game::settingsMenu, this);

    auto exitBtn = tgui::Button::create("Выйти из игры");
    exitBtn->setOrigin(sf::Vector2f(0.5, 0.5));
    exitBtn->setSize({400, 100});
    exitBtn->setPosition({"50%", 460});
    exitBtn->setTextSize(50);
    exitBtn->onClick(&Game::exitBtn, this);

    auto inventorySlot1 = tgui::BitmapButton::create();
    inventorySlot1->setImage("./assets/ui/active_slot_64x64.png");
    inventorySlot1->setOrigin(sf::Vector2f(0.5, 0.5));
    inventorySlot1->setPosition({"50%-120", "100%-64"});
    auto inventorySlot2 = tgui::BitmapButton::create();
    inventorySlot2->setImage("./assets/ui/active_slot_64x64.png");
    inventorySlot2->setOrigin(sf::Vector2f(0.5, 0.5));
    inventorySlot2->setPosition({"50%-40", "100%-64"});
    auto inventorySlot3 = tgui::BitmapButton::create();
    inventorySlot3->setImage("./assets/ui/active_slot_64x64.png");
    inventorySlot3->setOrigin(sf::Vector2f(0.5, 0.5));
    inventorySlot3->setPosition({"50%+40", "100%-64"});
    auto inventorySlot4 = tgui::BitmapButton::create();
    inventorySlot4->setImage("./assets/ui/active_slot_64x64.png");
    inventorySlot4->setOrigin(sf::Vector2f(0.5, 0.5));
    inventorySlot4->setPosition({"50%+120", "100%-64"});

    auto inventoryBtn = tgui::BitmapButton::create();
    inventoryBtn->setImage("./assets/ui/backpack_64x64.png");
    inventoryBtn->setOrigin(sf::Vector2f(0.5, 0.5));
    inventoryBtn->setPosition({"50%+180", "100%-64"});

    auto inventoryLock1 = tgui::BitmapButton::create();
    inventoryLock1->setImage("./assets/ui/lock_64x_64.png");
    inventoryLock1->setOrigin(sf::Vector2f(0.5, 0.5));
    inventoryLock1->setPosition({"50%-120", "100%-64"});
    auto inventoryLock2 = tgui::BitmapButton::create();
    inventoryLock2->setImage("./assets/ui/lock_64x_64.png");
    inventoryLock2->setOrigin(sf::Vector2f(0.5, 0.5));
    inventoryLock2->setPosition({"50%-40", "100%-64"});
    auto inventoryLock3 = tgui::BitmapButton::create();
    inventoryLock3->setImage("./assets/ui/lock_64x_64.png");
    inventoryLock3->setOrigin(sf::Vector2f(0.5, 0.5));
    inventoryLock3->setPosition({"50%+40", "100%-64"});
    auto inventoryLock4 = tgui::BitmapButton::create();
    inventoryLock4->setImage("./assets/ui/lock_64x_64.png");
    inventoryLock4->setOrigin(sf::Vector2f(0.5, 0.5));
    inventoryLock4->setPosition({"50%+120", "100%-64"});

    this->gui->add(startBtn);
    this->gui->add(continueBtn);
    this->gui->add(settingsBtn);
    this->gui->add(exitBtn);

    this->inventoryGui->add(inventorySlot1);
    this->inventoryGui->add(inventorySlot2);
    this->inventoryGui->add(inventorySlot3);
    this->inventoryGui->add(inventorySlot4);
    this->inventoryGui->add(inventoryLock1);
    this->inventoryGui->add(inventoryLock2);
    this->inventoryGui->add(inventoryLock3);
    this->inventoryGui->add(inventoryLock4);
    this->inventoryGui->add(inventoryBtn);
}

void Game::run()
{
    std::cout << BOLDGREEN << "=== Game run ===\n"
              << RESET;

    this->_player->init(sf::Vector2f(0.0, 0.0), sf::IntRect(0, 0, 512, 1024), &deltaTime);
    std::function<bool(sf::Vector2f)> event = std::bind(&Game::collidePoint, this, std::placeholders::_1);
    this->_player->bindCollision(event);

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
        this->_player->triggerLoop();
        eventHandler.handleEvent(*window);
        keyboardHandler.handleKeyboard();

        if (!this->gameRunning)
        {
            window->clear(sf::Color(30, 86, 99));
            this->gui->draw();
            window->display();
            continue;
        }

        if (this->_player->isIdle())
        {
            // FIXME: фикс бага анимации
            this->_player->movePlayer(sf::Vector2f(0.0, 0.0));
        }

        camera.setPosition(this->_player->getPosition());

        window->clear();

        window->draw(*levels["start"]);
        window->draw(*this->_player);

        fps_text.setString("FPS: " + std::to_string(fps));
        fps_text.setPosition(window->mapPixelToCoords(sf::Vector2i(5, 5)));
        window->draw(fps_text);

        // dtime_text.setString("Delta time: " + std::to_string((int)(dtime * 1000)));
        // dtime_text.setPosition(window->mapPixelToCoords(sf::Vector2i(5, 5)));
        // window->draw(dtime_text);

        if (!this->gameRunning)
        {
            this->gui->draw();
        }
        else
        {
            this->inventoryGui->draw();
        }

        window->display();

        dtime = deltaTime.loop();
        fps = (int)std::round(1.0f / dtime);
    }

    std::cout << BOLDRED << "=== Game exit ===" << RESET << std::endl;
}