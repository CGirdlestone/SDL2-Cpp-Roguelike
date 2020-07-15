
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
      for (int i = 0; i < static_cast<int>(m_entities->size()); i++){
        if (i == uid){ continue; }
        if (m_entities->at(i)->fighter == nullptr){ continue; }
        if (!(m_entities->at(i)->fighter->isAlive)){ continue; }

        if (m_entities->at(uid)->position->x + dx == m_entities->at(i)->position->x && m_entities->at(uid)->position->y + dy == m_entities->at(i)->position->y && m_entities->at(i)->fighter->isAlive){
          AttackEvent attackEvent = AttackEvent(uid, i);
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
    m_entities->at(uid)->position->x += dx;
    m_entities->at(uid)->position->y += dy;

    if (uid == 0){
      m_dungeon->recomputeFOV = true;
    }
  }
}
