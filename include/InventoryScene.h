#ifndef INVENTORYSCENE_H
#define INVENTORYSCENE_H

#include <vector>
#include "SDL2/SDL.h"
#include "Renderer.h"
#include "KeyPressSurfaces.h"
#include "EventManager.h"
#include "Scene.h"
#include "GameObject.h"
#include "DungeonGenerator.h"
#include "Camera.h"
#include "MessageLog.h"

class InventoryScene : public Scene
{
public:
  InventoryScene(EventManager *eventManager, Renderer *renderer, std::vector<GameObject*> *entities);
  virtual ~InventoryScene();
  enum KeyPressSurfaces getEvent(SDL_Event* e);
  void render();
  void handleInput(KeyPressSurfaces keyPress);
  void processEntities();
  void update(Uint32 dt);
  void onTick();

private:
  EventManager *m_eventManager;
  Renderer *m_renderer;
  std::vector<GameObject*> *m_entities;
	int m_index;
};

#endif
