
#include <iostream>
#include <map>
#include "MoveSystem.h"
#include "Events.h"
#include "EventTypes.h"
#include "EventManager.h"


MoveSystem::MoveSystem(EventManager* eventManager, std::map<int, GameObject*> *entities, DungeonGenerator* dungeon):
m_eventManager(eventManager), m_entities(entities), m_dungeon(dungeon)
{
  m_eventManager->registerSystem(MOVE, this);
}

MoveSystem::~MoveSystem()
{
  m_eventManager = nullptr;
  m_entities = nullptr;
  m_dungeon = nullptr;
}

bool MoveSystem::checkMove(int dx, int dy, int uid)
{
  if (m_entities->at(uid)->position->x + dx>= 0 && m_entities->at(uid)->position->x + dx < m_dungeon->Getm_width() && m_entities->at(uid)->position->y + dy >= 0 && m_entities->at(uid)->position->y + dy < m_dungeon->Getm_height()){
    if (m_dungeon->m_level[(m_entities->at(uid)->position->x + dx) + m_dungeon->Getm_width() * (m_entities->at(uid)->position->y + dy)] != '.'){
      return false;
    } else{
			std::map<int, GameObject*>::iterator it;
      for (it = m_entities->begin(); it != m_entities->end(); ++it){
        if (it->first == uid){ continue; }
        if (it->second->fighter == nullptr){ continue; }
        if (!(it->second->fighter->isAlive)){ continue; }

        if (m_entities->at(uid)->position->x + dx == it->second->position->x && m_entities->at(uid)->position->y + dy == it->second->position->y && it->second->fighter->isAlive){
          AttackEvent attackEvent = AttackEvent(uid, it->first);
          m_eventManager->pushEvent(attackEvent);
          return false;
        }
      }
      return true;
    }
  } else {
    return false;
  }
}

void MoveSystem::moveEntity(int dx, int dy, int uid)
{
  if (checkMove(dx, dy, uid)){
    int previousPos = m_entities->at(uid)->position->x + m_entities->at(uid)->position->y * m_dungeon->Getm_width();

		m_entities->at(uid)->position->x += dx;
    m_entities->at(uid)->position->y += dy;
	
    int newPos = m_entities->at(uid)->position->x + m_entities->at(uid)->position->y * m_dungeon->Getm_width();
		m_dungeon->removeObjectFromTile(m_entities->at(uid), previousPos);
		m_dungeon->moveObjectToTile(m_entities->at(uid), newPos);		

    if (uid == 0){
      m_dungeon->recomputeFOV = true;
    }
  }
}
