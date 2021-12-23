#include <SFML/Graphics.hpp>
#include "Game.hpp"

int main()
{
    Game game("Hora Gladiis", sf::Vector2i(1000, 600), 60, false);
    game.init();
    game.run();

    return 0;
}
