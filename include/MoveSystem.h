#ifndef MOVESYSTEM_H
#define MOVESYSTEM_H

#include "System.h"
#include "Events.h"
#include "GameObject.h"
#include "DungeonGenerator.h"

#include <map>

class EventManager;

class MoveSystem : public System
{
public:
  MoveSystem(EventManager* eventManager, std::map<int, GameObject*> *entities, DungeonGenerator* dungeon);
  virtual ~MoveSystem();
  bool checkMove(int dx, int dy, int uid);
  void moveEntity(int dx, int dy, int uid);
  virtual void notify(MoveEvent event) override {moveEntity(event.m_dx, event.m_dy, event.m_uid);};



private:
  EventManager* m_eventManager;
  std::map<int, GameObject*> *m_entities;
  DungeonGenerator* m_dungeon;
};

#endif
