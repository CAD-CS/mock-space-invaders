#include <string>
#include "core/Game.hpp"
#include <iostream>

const int WINDOW_WIDTH = 1900;
const int WINDOW_HEIGHT = 1000;

int main()
{
    try
    {
        std::cout << "Initializing Game." << std::endl;
        Game game(static_cast<unsigned int>(WINDOW_WIDTH), static_cast<unsigned int>(WINDOW_HEIGHT), "Mock Invaders");
        std::cout << "Game started." << std::endl;
        game.run();
        std::cout << "Game exited." << std::endl;
    }
    catch (const std::exception& e)
    {
        std::cout << "Exception: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    catch (...)
    {
        std::cout << "Unknown exception occurred." << std::endl;
        return EXIT_FAILURE;
    }
    return 0;
}
