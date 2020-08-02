
#ifndef INVENTORYSYSTEM_H
#define INVENTORYSYSTEM_H

#include <map>
#include "System.h"
#include "Events.h"
#include "GameObject.h"
#include "DungeonGenerator.h"

class EventManager;

class InventorySystem : public System
{
public:
  InventorySystem(EventManager* eventManager, std::map<int, GameObject*> *entities, DungeonGenerator *dungeon);
  virtual ~InventorySystem();
  void pickUpItem(TakeEvent event);
	void dropItem(DropEvent event);
	void equipItem(EquipEvent event);
	void unequipItem(UnequipEvent event);
	void useItem(UseItemEvent event);
	void decreaseUses(GameObject* item, int user_uid, int item_uid);

	virtual void notify(DropEvent event);
  virtual void notify(TakeEvent event);
	virtual void notify(EquipEvent event);
	virtual void notify(UnequipEvent event);
	virtual void notify(UseItemEvent event);

private:
  EventManager* m_eventManager;
  std::map<int, GameObject*> *m_entities;
	DungeonGenerator *m_dungeon;
};


#endif
