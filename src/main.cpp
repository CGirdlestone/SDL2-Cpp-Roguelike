#include <iostream>
#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#include "SDL2/SDL_image.h"

#include "Game.h"

using namespace std;

int main()
{
    Game* game = new Game();
    if(game->init(100, 50, 16, (char*)"Game!")){
        game->run();
    }
    return 0;
}
