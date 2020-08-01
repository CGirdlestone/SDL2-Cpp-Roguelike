#ifndef GAMESTATEMANAGER_H
#define GAMESTATEMANAGER_H

#include <vector>
#include <map>
#include "SDL2/SDL.h"
#include "System.h"
#include "Events.h"
#include "GameObject.h"
#include "Scene.h"
#include "GameScene.h"
#include "StartScene.h"
#include "InventoryScene.h"
#include "CharacterScene.h"
#include "TargetingScene.h"
#include "PauseScene.h"
#include "GameOverScene.h"
#include "SceneTypes.h"


class EventManager;

class GameStateManager : public System
{
public:
  GameStateManager(EventManager* eventManager, std::map<int, GameObject*> *entities);
  virtual ~GameStateManager();
  void notify(PushScene event);
  void notify(PopScene event);
  void notify(QuitEvent event);
  void notify(PassUserInfoEvent event);
	void notify(DeadEvent event);
	void notify(PlayerTurnOverEvent event);
	void notify(LoadEvent event);
	void notify(RestartEvent event);
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
	CharacterScene *m_characterScene;
	TargetingScene *m_targetingScene;
	PauseScene *m_pauseScene;
	GameOverScene *m_gameOverScene;

private:
  EventManager* m_eventManager;
  std::map<int, GameObject*> *m_entities;
  std::vector<Scene*> m_sceneStack;
};
#endif
