#ifndef GAMESTATEMANAGER_H
#define GAMESTATEMANAGER_H

#include <vector>
#include "SDL2/SDL.h"
#include "System.h"
#include "Events.h"
#include "GameObject.h"
#include "Scene.h"
#include "GameScene.h"
#include "StartScene.h"
#include "InventoryScene.h"
#include "SceneTypes.h"

class EventManager;

class GameStateManager : public System
{
public:
  GameStateManager(EventManager* eventManager, std::vector<GameObject*> *entities);
  virtual ~GameStateManager();
  void notify(PushScene event);
  void notify(PopScene event);
  void notify(QuitEvent event);
  void pushScene(SceneTypes scene);
  void popScene(int i);
  void render();
  void processInput(SDL_Event *e);
  void update(Uint32 dt);
  void onTick();
  bool playing;
  StartScene *m_startScene;
  GameScene *m_gameScene;
	InventoryScene *m_inventoryScene;

private:
  EventManager* m_eventManager;
  std::vector<GameObject*> *m_entities;
  std::vector<Scene*> m_sceneStack;
};
#endif
