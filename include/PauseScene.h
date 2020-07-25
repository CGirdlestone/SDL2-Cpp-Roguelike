#ifndef PAUSESCENE_H
#define PAUSESCENE_H

#include <map>
#include "SDL2/SDL.h"
#include "Renderer.h"
#include "Camera.h"
#include "DungeonGenerator.h"
#include "MessageLog.h"
#include "KeyPressSurfaces.h"
#include "EventManager.h"
#include "Scene.h"

class PauseScene :public Scene
{
public:
  PauseScene(EventManager *eventManager, Renderer *renderer, Camera *camera, DungeonGenerator *dungeon, std::map<int, GameObject*> *actors, MessageLog *messageLog);
  virtual ~PauseScene();
  enum KeyPressSurfaces getEvent(SDL_Event* e);
  void render();
  void handleInput(KeyPressSurfaces keyPress);
  void update(Uint32 dt);
  void onTick();
	void resetIndex(){m_i = 0; };

private:
  EventManager *m_eventManager;
  Renderer *m_renderer;
	Camera *m_camera;
	DungeonGenerator *m_dungeon;
	std::map<int, GameObject*> *m_entities;
	MessageLog *m_messageLog;
  int m_i;
};

#endif
