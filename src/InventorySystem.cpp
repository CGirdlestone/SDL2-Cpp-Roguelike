

#include <vector>

#include "InventorySystem.h"
#include "EventManager.h"
#include "Events.h"
#include "EventTypes.h"

InventorySystem::InventorySystem(EventManager* eventManager, std::vector<GameObject*> *entities):
m_eventManager(eventManager), m_entities(entities)
{
  m_eventManager->registerSystem(TAKE, this);
}

InventorySystem::~InventorySystem()
{
  m_eventManager = nullptr;
  m_entities = nullptr;
}

void InventorySystem::pickUpItem(TakeEvent event)
{

  for (int i = 0; i < static_cast<int>(m_entities->size()); ++i){
    if(event.m_uid == i){ continue; }
    if(m_entities->at(i)->position == nullptr){ continue; }

    if (m_entities->at(i)->position->x == event.m_x && m_entities->at(i)->position->y == event.m_y){
      m_entities->at(event.m_uid)->inventory->inventory.push_back(m_entities->at(i));
      delete m_entities->at(i)->position;
      m_entities->at(i)->position = nullptr;
      m_eventManager->pushEvent(OnPickUpEvent(event.m_uid, m_entities->at(i)->m_name));
      break;
    }
  }
}

void InventorySystem::notify(TakeEvent event)
{
  pickUpItem(event);
}
