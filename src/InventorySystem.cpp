

#include <vector>

#include "InventorySystem.h"
#include "EventManager.h"
#include "Events.h"
#include "EventTypes.h"
#include "Components.h"

InventorySystem::InventorySystem(EventManager* eventManager, std::vector<GameObject*> *entities):
m_eventManager(eventManager), m_entities(entities)
{
  m_eventManager->registerSystem(TAKE, this);
	m_eventManager->registerSystem(DROP, this);
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

void InventorySystem::dropItem(DropEvent event)
{
	// TO DO
	int x = m_entities->at(event.m_actor_uid)->position->x;
	int y = m_entities->at(event.m_actor_uid)->position->y;

	for (int i = 0; i < static_cast<int>(m_entities->at(event.m_actor_uid)->inventory->inventory.size()); ++i){
		if (m_entities->at(event.m_actor_uid)->inventory->inventory.at(i)->m_uid == event.m_item_uid){
			m_entities->at(event.m_actor_uid)->inventory->inventory.erase(m_entities->at(event.m_actor_uid)->inventory->inventory.begin() + i);
			m_entities->at(event.m_item_uid)->position = new Position(x, y);
		}
	}
}

void InventorySystem::notify(TakeEvent event)
{
  pickUpItem(event);
}

void InventorySystem::notify(DropEvent event)
{
	dropItem(event);
}
