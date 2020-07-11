#ifndef SCENE_H
#define SCENE_H

#include "SDL2/SDL.h"
#include "KeyPressSurfaces.h"

class Scene
{
public:
  virtual ~Scene() { };
  virtual void render() = 0;
  virtual enum KeyPressSurfaces getEvent(SDL_Event* e) = 0;
  virtual void handleInput(KeyPressSurfaces keyPress) = 0;
  virtual void update(Uint32 dt) = 0;
  virtual void onTick() = 0;
};

#endif
