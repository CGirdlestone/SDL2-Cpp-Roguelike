#ifndef GAMESCENE_H
#define GAMESCENE_H

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

class GameScene : public Scene
{
public:
  GameScene(EventManager *eventManager, Renderer *renderer, std::map<int, GameObject*> *entities, Camera* camera, DungeonGenerator* dungeon, MessageLog* messageLog);
  virtual ~GameScene();
  enum KeyPressSurfaces getEvent(SDL_Event* e);
  void render();
  void handleInput(KeyPressSurfaces keyPress);
  void processEntities();
  void update(Uint32 dt);
  void onTick();
	void newGame();


private:
  EventManager *m_eventManager;
  Renderer *m_renderer;
  std::map<int, GameObject*> *m_entities;
  Camera* m_camera;
  DungeonGenerator *m_dungeon;
  MessageLog *m_messageLog;
  bool m_playerTurn;
};

#endif
