#ifndef CHARACTERSCENE_H
#define CHARACTERSCENE_H

#include <map>
#include "SDL2/SDL.h"
#include "Renderer.h"
#include "KeyPressSurfaces.h"
#include "EventManager.h"
#include "Scene.h"
#include "GameObject.h"
#include "DungeonGenerator.h"
#include "Camera.h"
#include "MessageLog.h"

class CharacterScene : public Scene
{
public:
  CharacterScene(EventManager *eventManager, Renderer *renderer, std::map<int, GameObject*> *entities);
  virtual ~CharacterScene();
  enum KeyPressSurfaces getEvent(SDL_Event* e);
  void render();
  void handleInput(KeyPressSurfaces keyPress);
  void processEntities();
  void update(Uint32 dt);
  void onTick();

private:
  EventManager *m_eventManager;
  Renderer *m_renderer;
  std::map<int, GameObject*> *m_entities;
	int m_index;
};

#endif
