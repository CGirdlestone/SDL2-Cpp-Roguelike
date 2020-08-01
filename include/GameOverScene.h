#ifndef GAMEOVERSCENE_H
#define GAMEOVERSCENE_H

#include <string>

#include "SDL2/SDL.h"
#include "Renderer.h"
#include "KeyPressSurfaces.h"
#include "EventManager.h"
#include "Scene.h"

class GameOverScene :public Scene
{
public:
  GameOverScene(EventManager *eventManager, Renderer *renderer);
  virtual ~GameOverScene();
  enum KeyPressSurfaces getEvent(SDL_Event* e);
  void render();
  void handleInput(KeyPressSurfaces keyPress);
  void update(Uint32 dt);
  void onTick();
	void loadDeathMessage();
	std::vector<std::string> m_deathMessages;
	bool deleteSave();

private:
  EventManager *m_eventManager;
  Renderer *m_renderer;
  int m_i;
	Uint32 timer;
	Uint32 ticks;
	std::vector<std::string> m_completeDeathMessages;
	int numChars;
	int numLines;
};

#endif
