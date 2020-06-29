#ifndef COMPONENTS_H
#define COMPONENTS_H

#include "SDL2/SDL.h"

struct Position
{
  int x;
  int y;
};

struct Renderable
{
  char chr;
  SDL_Color colour;
};

#endif
