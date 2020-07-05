#include <iostream>
#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#include "SDL2/SDL_image.h"

#include "Game.h"

using namespace std;

int main()
{
  Game* game = new Game();
  if(game->init(150, 80, 90, 50, 16, (char*)"Game!", 60)){
      game->run();
  }
  return 0;
}
