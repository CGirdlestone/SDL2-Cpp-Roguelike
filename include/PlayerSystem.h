
#ifndef PLAYERSYSTEM_H
#define PLAYERSYSTEM_H

#include <map>
#include "System.h"
#include "Events.h"
#include "GameObject.h"

class EventManager;

class PlayerSystem : public System
{
public:
  PlayerSystem(EventManager* eventManager, std::map<int, GameObject*> *entities);
  virtual ~PlayerSystem();
  void onDead(DeadEvent event);
	void checkLevelUp();
	void increaseThreshold();
	void increaseLevel();

  virtual void notify(DeadEvent event);
private:
  EventManager* m_eventManager;
  std::map<int, GameObject*> *m_entities;
};


#endif
