#include <SFML/Graphics.hpp>
#include "Game.hpp"

int main()
{
    while (true)
    {
        Game game("Hora Gladiis", sf::Vector2i(1000, 600), 60, false);
        game.init();
        game.run();

        if (game.exitStatus != GameExitStatus::NewGame)
        {
            break;
        }
    }

    return 0;
}
