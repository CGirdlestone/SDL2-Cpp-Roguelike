
#ifndef INVENTORYSYSTEM_H
#define INVENTORYSYSTEM_H

#include <vector>
#include "System.h"
#include "Events.h"
#include "GameObject.h"

class EventManager;

class InventorySystem : public System
{
public:
  InventorySystem(EventManager* eventManager, std::vector<GameObject*> *entities);
  virtual ~InventorySystem();
  void pickUpItem(TakeEvent event);
	void dropItem(DropEvent event);
	void equipItem(EquipEvent event);
	void unequipItem(UnequipEvent event);

	virtual void notify(DropEvent event);
  virtual void notify(TakeEvent event);
	virtual void notify(EquipEvent event);
	virtual void notify(UnequipEvent event);
private:
  EventManager* m_eventManager;
  std::vector<GameObject*> *m_entities;
};


#endif
