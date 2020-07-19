

#include <map>
#include <iostream>
#include <cstdlib>
#include "InventorySystem.h"
#include "EventManager.h"
#include "Events.h"
#include "EventTypes.h"
#include "Components.h"
#include "UseableFunctionEnum.h"

InventorySystem::InventorySystem(EventManager* eventManager, std::map<int, GameObject*> *entities):
m_eventManager(eventManager), m_entities(entities)
{
  m_eventManager->registerSystem(TAKE, this);
	m_eventManager->registerSystem(DROP, this);
	m_eventManager->registerSystem(EQUIP, this);
	m_eventManager->registerSystem(UNEQUIP, this);
	m_eventManager->registerSystem(USEITEM, this);
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
		if(m_entities->at(i)->item == nullptr){ continue; }

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
	int x = m_entities->at(event.m_actor_uid)->position->x;
	int y = m_entities->at(event.m_actor_uid)->position->y;

	for (int i = 0; i < static_cast<int>(m_entities->at(event.m_actor_uid)->inventory->inventory.size()); ++i){
		if (m_entities->at(event.m_actor_uid)->inventory->inventory.at(i)->m_uid == event.m_item_uid){
			m_entities->at(event.m_actor_uid)->inventory->inventory.erase(m_entities->at(event.m_actor_uid)->inventory->inventory.begin() + i);
			m_entities->at(event.m_item_uid)->position = new Position(x, y);
		}
	}
}

void InventorySystem::equipItem(EquipEvent event)
{
	if (m_entities->at(event.m_item_uid)->wearable != nullptr){
		if (m_entities->at(event.m_actor_uid)->body->slots.at(m_entities->at(event.m_item_uid)->wearable->slot) != nullptr){
			m_entities->at(event.m_actor_uid)->inventory->inventory.push_back(m_entities->at(event.m_actor_uid)->body->slots.at(m_entities->at(event.m_item_uid)->wearable->slot));
		}
	
		m_entities->at(event.m_actor_uid)->body->slots[m_entities->at(event.m_item_uid)->wearable->slot] = m_entities->at(event.m_item_uid);

		for (int i = 0; i < static_cast<int>(m_entities->at(event.m_actor_uid)->inventory->inventory.size()); ++i){
			if (m_entities->at(event.m_actor_uid)->inventory->inventory.at(i)->m_uid == event.m_item_uid){
				m_entities->at(event.m_actor_uid)->inventory->inventory.erase(m_entities->at(event.m_actor_uid)->inventory->inventory.begin() + i);
				break;
			}
		}
	}
}

void InventorySystem::unequipItem(UnequipEvent event)
{
	GameObject* item = m_entities->at(event.m_actor_uid)->body->slots[static_cast<EquipSlots>(event.m_slotNum)];

	m_entities->at(event.m_actor_uid)->body->slots[static_cast<EquipSlots>(event.m_slotNum)] = nullptr;

	m_entities->at(event.m_actor_uid)->inventory->inventory.push_back(item);
}

void InventorySystem::useItem(UseItemEvent event)
{
	GameObject* item = m_entities->at(event.m_item_uid);

	if (item->useable != nullptr){
		if(item->useable->funcToDo == HEALING){
			if (m_entities->at(event.m_user_uid)->fighter->health < m_entities->at(event.m_user_uid)->fighter->maxHealth){
				--item->useable->numUses;
				m_eventManager->pushEvent(DamageEvent(event.m_user_uid, -1 * (std::rand()%item->healing->roll + 1)));
			} 
		} else if (item->useable->funcToDo == DIRECTDAMAGE){
			if (event.m_target_uid == -1){
				// need to go into targeting screen
			} else {
				// this has a defined target already
			}
		} else if (item->useable->funcToDo == AOE){
			if (event.m_target_uid == -1){
			
			} else {

			}
		} else if (item->useable->funcToDo == STATUS){
			if (event.m_target_uid == -1){

			} else {

			}
		}
		if (item->useable->numUses <= 0){
			for (int i = 0; i < static_cast<int>(m_entities->at(event.m_user_uid)->inventory->inventory.size()); ++i){
				if (m_entities->at(event.m_user_uid)->inventory->inventory.at(i)->m_uid == event.m_item_uid){
					m_entities->at(event.m_user_uid)->inventory->inventory.erase(m_entities->at(event.m_user_uid)->inventory->inventory.begin() + i);
				}
			}
			delete m_entities->at(event.m_item_uid);
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

void InventorySystem::notify(EquipEvent event)
{
	equipItem(event);
}

void InventorySystem::notify(UnequipEvent event)
{
	unequipItem(event);
}

void InventorySystem::notify(UseItemEvent event)
{
	useItem(event);
}

