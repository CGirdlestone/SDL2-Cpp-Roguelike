#ifndef LOOTMANAGER_H
#define LOOTMANAGER_H

#include <string>
#include <map>
#include "System.h"
#include "DungeonGenerator.h"
#include "Events.h"
#include "Components.h"
#include "GameObject.h"
#include "EntityFactory.h"

struct Loot
{
	Loot(std::string _name, int _total, std::map<int, std::string>);
	~Loot();
	std::string name;
	int total;
	std::map<int, std::string> lootTable;
};

class LootManager : System
{
public:
	LootManager(EventManager* eventManager, DungeonGenerator* dungeon, std::map<int, GameObject*> *entities, EntityFactory* factory);
	~LootManager();
	void parseLootTables(std::string line);
	void loadLootTables(std::string filename);
	std::string getLoot(std::string name);
	void notify(DeadEvent event);
	void generateLoot(DeadEvent event);

private:
	std::map<std::string, Loot> masterLootTable;
	EventManager* m_eventManager;
	DungeonGenerator* m_dungeon;
	std::map<int, GameObject*> *m_entities;
	EntityFactory* m_factory;
};

#endif


