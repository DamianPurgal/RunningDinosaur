#include "Game.h"
#include <memory>

int main()
{
    {
        std::unique_ptr<Game> gra = std::make_unique<Game>();
        gra->startGame();
    } 
    return 0;
}
