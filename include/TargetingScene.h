#ifndef TARGETINGSCENE_H
#define TARGETINGSCENE_H

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

class TargetingScene : public Scene
{
public:
  TargetingScene(EventManager *eventManager, Renderer *renderer, std::map<int, GameObject*> *entities, Camera *camera, DungeonGenerator *dungeon, MessageLog *messageLog);
  virtual ~TargetingScene();
  enum KeyPressSurfaces getEvent(SDL_Event* e);
  void render();
  void handleInput(KeyPressSurfaces keyPress);
  void processEntities();
  void update(Uint32 dt);
  void onTick();
	void resetIndex(){m_x = m_entities->at(0)->position->x; m_y = m_entities->at(0)->position->y;};

	int m_user_uid, m_item_uid;
private:
  EventManager *m_eventManager;
  Renderer *m_renderer;
  std::map<int, GameObject*> *m_entities;
	Camera *m_camera;
	DungeonGenerator *m_dungeon;
	MessageLog *m_messageLog;
	int m_x, m_y;
};

#endif
