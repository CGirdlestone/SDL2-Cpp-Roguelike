#ifndef STARTSCENE_H
#define STARTSCENE_H

#include "SDL2/SDL.h"
#include "Renderer.h"
#include "KeyPressSurfaces.h"
#include "EventManager.h"
#include "Scene.h"

class StartScene :public Scene
{
public:
  StartScene(EventManager *eventManager, Renderer *renderer);
  virtual ~StartScene();
  enum KeyPressSurfaces getEvent(SDL_Event* e);
  void render();
  void handleInput(KeyPressSurfaces keyPress);
  void update(Uint32 dt);
  void onTick();

private:
  EventManager *m_eventManager;
  Renderer *m_renderer;
  int m_i;
	int m_options;
	bool hasSaveFile;
};

#endif
