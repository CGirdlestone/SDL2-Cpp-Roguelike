
#include "LootManager.h"
#include <cstdlib>
#include <sstream>
#include <fstream>
#include <string>
#include "EventManager.h"

Loot::Loot(std::string _name, int _total, std::map<int, std::string> _lootTable):
name(_name), total(_total), lootTable(_lootTable)
{
}

Loot::~Loot()
{
}

LootManager::LootManager(EventManager* eventManager, DungeonGenerator* dungeon, std::map<int, GameObject*> *entities, EntityFactory* factory):
m_eventManager(eventManager), m_dungeon(dungeon), m_entities(entities), m_factory(factory)
{
	m_eventManager->registerSystem(DEAD, this);
}

LootManager::~LootManager()
{
}

void LootManager::loadLootTables(std::string filename)
{
	std::ifstream file;
	std::string line;
	
	file.open(filename.c_str());
	if (file.is_open()){
		while (!file.eof()){
			getline(file, line);
			parseLootTables(line);
			if (file.eof()){ break; }
		}
	}
}

void LootManager::parseLootTables(std::string line)
{
	std::stringstream ss(line);

	std::string name;
	std::map<int, std::string> lootTable;

	std::string item;
	int itemChance;
	int total = 0;

	for (std::string l; getline(ss, l, ','); ){
		if (l.at(0) == ' '){
			l = l.substr(1, l.size());
		}
		
		if (l.substr(0, l.find(":")) == "NAME"){
			name = l.substr(l.find(":")+1, l.size());
			continue;
		}

		item = l.substr(0, l.find(":"));
		itemChance = std::stoi(l.substr(l.find(":")+1, l.size()));
		total += itemChance;
		
		lootTable.insert({total, item});
	}
	
	Loot lootBox = Loot(name, total, lootTable);

	masterLootTable.insert({name, lootBox});
}

std::string LootManager::getLoot(std::string name)
{
	int roll = rand()%masterLootTable.at(name).total + 1;

	std::string item = "";

	std::map<int, std::string>::iterator it;
	for(it = masterLootTable.at(name).lootTable.begin(); it != masterLootTable.at(name).lootTable.end(); ++it){
		if (roll <= it->first){
			item = it->second;
			break;
		}
	}
	return item;
}

void LootManager::generateLoot(DeadEvent event)
{
	std::string name = m_entities->at(event.m_uid)->m_name;
	std::string item = getLoot(name);

	if (item != "NONE"){
		GameObject* entity = new GameObject();

		m_factory->makeEntity(item, entity, m_entities->at(event.m_uid)->position->x, m_entities->at(event.m_uid)->position->y, m_entities);

		m_entities->insert({entity->m_uid, entity});
	}
}


void LootManager::notify(DeadEvent event)
{
	if (event.m_uid != 0){
		generateLoot(event);
	}
}
