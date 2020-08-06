#include "EntityFactory.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include "Components.h"
#include "GameObject.h"
#include "Slots.h"
#include "DamageTypes.h"
#include "SDL2/SDL.h"
#include "UseableFunctionEnum.h"
#include "StatusTypes.h"
#include "EntityType.h"

EntityFactory::EntityFactory()
{
	m_uid = 0;
}

EntityFactory::~EntityFactory()
{

}

void EntityFactory::loadData(std::string filename)
{
	std::ifstream file;
	std::string line;

	std::string name;
	std::vector<std::string> components;

	file.open(filename);
	if(file.is_open()){
		while(std::getline(file, line)){
			if(line == "\n"){continue;}
			if(line.substr(0, line.find(":")) == "NAME"){
				
				if (components.size() > 0){
					if (filename == "./resources/items.txt"){
						m_items.insert({name, components});
					} else if (filename == "./resources/mobs.txt"){
						m_mobs.insert({name, components});
					} else if (filename == "./resources/player.txt"){
						m_player.insert({name, components});
					}
					components.clear();
				}
				name = line.substr(line.find(":")+2, line.length());
			} else {
				components.push_back(line);
			}
		}
		if (components.size() > 0){
			if (filename == "./resources/items.txt"){
				m_items.insert({name, components});
			} else if (filename == "./resources/mobs.txt"){
				m_mobs.insert({name, components});
			} else if (filename == "./resources/player.txt"){
				m_player.insert({name, components});
			}
		}
	}
}

void EntityFactory::generateDistributions(){
	std::map<std::string, std::vector<std::string>>::iterator it;
	std::vector<std::string>::iterator vecIt;
	std::string line;
	int level, _exp;


	for (it = m_items.begin(); it != m_items.end(); ++it){
		for (vecIt = it->second.begin(); vecIt != it->second.end(); ++vecIt){
			line = (*vecIt);
			if (line.substr(0, line.find(":")) == "ITEM"){
				level = stoi(line.substr(line.find(";")+1, line.size()));
				break;
			}
		}
		if (m_itemDistribution.find(level) != m_itemDistribution.end()){
			m_itemDistribution.at(level).push_back(it->first);
		} else {
			std::vector<std::string> vec = {it->first};
			m_itemDistribution.insert({level, vec});
		}
	}

	for (it = m_mobs.begin(); it != m_mobs.end(); ++it){
		for (vecIt = it->second.begin(); vecIt != it->second.end(); ++vecIt){
			line = (*vecIt);
			if (line.substr(0, line.find(":")) == "AI"){
				std::stringstream ss(line.substr(line.find(":")+2, line.size()));
				ss >> _exp >> level;
				break;
			}
		}
		if (m_mobDistribution.find(level) != m_mobDistribution.end()){
			m_mobDistribution.at(level).push_back(it->first);
		} else {
			std::vector<std::string> vec = {it->first};
			m_mobDistribution.insert({level, vec});
		}		
	}
}

DamageTypes EntityFactory::getDamageTypeEnum(std::string stringEnum)
{
	if (stringEnum == "SLASHING"){
		return SLASHING;
	} else if (stringEnum == "PIERCING"){
		return PIERCING;
	} else if (stringEnum == "BLUDGEONING"){
		return BLUDGEONING;
	} else if (stringEnum == "FIRE"){
		return FIRE;
	} else if (stringEnum == "ICE"){
		return ICE;
	} else if (stringEnum == "FORCE"){
		return FORCE;
	} else if (stringEnum == "LIGHTNING"){
		return LIGHTNING;
	} else if (stringEnum == "POISON"){
		return POISON;
	}
}

EquipSlots EntityFactory::getEquipSlotEnum(std::string stringEnum)
{
	if (stringEnum == "HEAD"){
		return HEAD;
	} else if (stringEnum == "LEFTHAND"){
		return LEFTHAND;
	} else if (stringEnum == "RIGHTHAND"){
		return RIGHTHAND;
	} else if (stringEnum == "BODY"){
		return BODY;
	} else if (stringEnum == "NECK"){
		return NECK;
	} else if (stringEnum == "BACK"){
		return BACK;
	}
}

UseableFunctionEnums EntityFactory::getFunctionEnum(std::string stringEnum)
{
	if (stringEnum == "HEALING"){
		return HEALING;
	} else if (stringEnum == "DIRECTDAMAGE"){
		return DIRECTDAMAGE;
	} else if (stringEnum == "AREADAMAGE"){
		return AOE;
	} else if (stringEnum == "STATUS"){
		return STATUS;
	}
}

void EntityFactory::makeRenderableComponent(std::string line, GameObject* entity)
{
	std::stringstream ss(line);

	char chr;
	int red, green, blue;
	ss >> chr >> std::hex >> red >> std::hex >> green >> std::hex >> blue;
	
	SDL_Color colour = {red, green, blue};

	Renderable* r = new Renderable(chr, colour); 

	entity->renderable = r;
}

void EntityFactory::makeFighterComponent(std::string line, GameObject* entity)
{
	std::stringstream ss(line);

	int maxHealth, power, defence;

	ss >> maxHealth >> power >> defence;

	Fighter* f = new Fighter(maxHealth, power, defence);

	entity->fighter = f; 
}

void EntityFactory::makeItemComponent(std::string line, GameObject* entity)
{
	std::string desc = line.substr(0, line.find(";"));
	int level = stoi(line.substr(line.find(";")+1, line.size()));	

	Item* item = new Item(desc, level);

	entity->item = item;
}

void EntityFactory::makeWeaponComponent(std::string line, GameObject* entity)
{
	std::stringstream ss(line);
	
	std::string damageString;
	DamageTypes damageType;	
	int die;

	ss >> damageString >> die;

	damageType = getDamageTypeEnum(damageString);
	
	Weapon* weapon = new Weapon(damageType, die);

	entity->weapon = weapon;
}

void EntityFactory::makeArmourComponent(std::string line, GameObject* entity)
{
	std::stringstream ss(line);

	std::string resistanceString, weaknessString;
	DamageTypes resistanceEnum, weaknessEnum;
	int armourBonus;

	ss >> resistanceString >> weaknessString >> armourBonus;
	resistanceEnum = getDamageTypeEnum(resistanceString);
	weaknessEnum = getDamageTypeEnum(weaknessString);

	Armour* armour = new Armour(resistanceEnum, weaknessEnum, armourBonus);

	entity->armour = armour;
}

void EntityFactory::makeWearableComponent(std::string line, GameObject* entity)
{
	std::stringstream ss(line);

	std::string equipSlotString;
	EquipSlots slot;

	ss >> equipSlotString;
	slot = getEquipSlotEnum(equipSlotString);

	Wearable* wearable = new Wearable(slot);

	entity->wearable = wearable;
}

void EntityFactory::makeAIComponent(std::string line, GameObject* entity)
{
	std::stringstream ss(line);

	int exp, level;

	ss >> exp >> level;
	
	AI* ai = new AI(exp, level);

	entity->ai = ai;
}

void EntityFactory::makeActorComponent(GameObject* entity)
{
	Actor* actor = new Actor();

	entity->actor = actor;
}

void EntityFactory::makeBodyComponent(GameObject* entity)
{
	Body* body = new Body();

	entity->body = body;
}

void EntityFactory::makePositionComponent(GameObject* entity, int x, int y)
{
	Position* pos = new Position(x, y);

	entity->position = pos;
}

void EntityFactory::makeInventoryComponent(std::string line, GameObject* entity)
{
	std::stringstream ss(line);

	int capacity;

	ss >> capacity;

	Inventory* inventory = new Inventory(capacity);

	entity->inventory = inventory;
}

void EntityFactory::makePlayerComponent(GameObject* entity)
{
	Player* p = new Player();

	entity->player = p;
}

void EntityFactory::makeUseableComponent(std::string line, GameObject* entity)
{	
	std::stringstream ss(line);
	std::string functionString;	
	int numUses;
	
	ss >> functionString >> numUses;

	UseableFunctionEnums functionEnum = getFunctionEnum(functionString);
	
	Useable* u = new Useable(functionEnum, numUses);

	entity->useable = u;
}

void EntityFactory::makeHealingComponent(std::string line, GameObject* entity)
{
	std::stringstream ss(line);
	int roll;

	ss >> roll;

	Healing* h = new Healing(roll);

	entity->healing = h;
}

void EntityFactory::makeDamageComponent(std::string line, GameObject* entity)
{
	std::stringstream ss(line);
	int roll, radius, chance;
	std::string damageTypeString;
	DamageTypes damageType;
	
	ss >> radius >> roll >> damageTypeString >> chance;

	damageType = getDamageTypeEnum(damageTypeString);
	
	Damage *d = new Damage(radius, roll, damageType, chance);
	
	entity->damage = d;	
}

void EntityFactory::makeAreaDamageComponent(std::string line, GameObject* entity)
{
	std::stringstream ss(line);
	int roll, radius, chance, splashRadius;
	std::string damageTypeString;
	DamageTypes damageType;
	
	ss >> radius >> splashRadius >> roll >> damageTypeString >> chance;

	damageType = getDamageTypeEnum(damageTypeString);
	
	AreaDamage *aoe = new AreaDamage(radius, roll, splashRadius, damageType, chance);
	
	entity->areaDamage = aoe;	
}

void EntityFactory::makeStatusComponent(std::string line, GameObject* entity)
{

}

void EntityFactory::makeConsumableComponent(GameObject* entity)
{
	Consumable* c = new Consumable();

	entity->consumable = c;
}

int EntityFactory::simulateNormalDistribution(int level){
	int score = 0;
	int mean = 6;
	int numRolls = 6;
	int numSides = 3;
	
	for (int i = 0; i < numRolls; ++i){
		score += rand() % numSides + 1;
	}
	
	return score + level - mean - numRolls > 0 ? score + level - mean - numRolls : 1;
}

std::string EntityFactory::chooseRandomMob(int level){
	int mobLevel;
	int randomIndex;	
	std::string entityName;

	mobLevel = simulateNormalDistribution(level);

	if (m_mobDistribution.find(mobLevel) != m_mobDistribution.end()){
		randomIndex = rand() % m_mobDistribution.at(mobLevel).size();
		entityName = m_mobDistribution.at(mobLevel).at(randomIndex);
		return entityName;
	}

	return chooseRandomMob(level);
}

std::string EntityFactory::chooseRandomItem(int level){
	int itemLevel;
	int randomIndex;
	std::string entityName;

	itemLevel = simulateNormalDistribution(level);
	
	if (m_itemDistribution.find(itemLevel) != m_itemDistribution.end()){
		randomIndex = rand() % m_mobDistribution.at(itemLevel).size();
		entityName = m_itemDistribution.at(itemLevel).at(randomIndex);
		return entityName;
	}

	return chooseRandomItem(level);
}

void EntityFactory::parseStartingItems(std::string line, GameObject* entity, std::map<int, GameObject*> *entities)
{
	std::string itemName;
	std::stringstream ss(line);
	while (std::getline(ss, itemName, ';')){
		if (itemName.size() == 0){ break; }

		itemName = itemName.substr(1, itemName.size());
		GameObject* item = new GameObject();
		makeEntity(itemName, item, entities);
		if (item->wearable != nullptr){
			entity->body->slots.at(item->wearable->slot) = item;
		} else {
			entity->inventory->inventory.push_back(item);
		}
		entities->insert({item->m_uid, item});
	}
}

void EntityFactory::makeEntity(std::string entityName, GameObject* entity, std::map<int, GameObject*> *entities)
{
	std::vector<std::string> components;
	
	if (m_mobs.find(entityName) != m_mobs.end()){
		components = m_mobs.at(entityName);
	}

	if (m_items.find(entityName) != m_items.end()){
		components = m_items.at(entityName);
	}

	if (m_player.find(entityName) != m_player.end()){
		components = m_player.at(entityName);
	}

	entity->m_name = entityName;
	entity->m_uid = m_uid;
	++m_uid;

	std::string component;
	std::string stats;

	for (std::string s : components){
		component = s.substr(0, s.find(":"));
		stats = s.substr(s.find(":")+1, s.length());
		if (component == "RENDERABLE"){
			makeRenderableComponent(stats, entity);
		} else if (component == "FIGHTER"){
			makeFighterComponent(stats, entity);
		} else if (component ==  "ACTOR"){
			makeActorComponent(entity);
		} else if (component ==  "AI"){
			makeAIComponent(stats, entity);
		} else if (component == "PLAYER"){
			makePlayerComponent(entity);
		} else if (component ==  "ITEM"){
			makeItemComponent(stats, entity);
		} else if (component == "WEAPON"){
			makeWeaponComponent(stats, entity);
		} else if (component ==  "ARMOUR"){
			makeArmourComponent(stats, entity);
		} else if (component ==  "WEARABLE"){
			makeWearableComponent(stats, entity);
		} else if (component ==  "BODY"){
			makeBodyComponent(entity);
		} else if (component == "INVENTORY"){
			makeInventoryComponent(s, entity);
		} else if (component == "USEABLE"){
			makeUseableComponent(stats, entity);
		} else if (component == "HEALING"){
			makeHealingComponent(stats, entity);
		} else if (component == "DIRECTDAMAGE"){
			makeDamageComponent(stats, entity);
		} else if (component == "AREADAMAGE"){
			makeAreaDamageComponent(stats, entity);
		} else if (component == "STATUS"){
			makeStatusComponent(stats, entity);
		} else if (component == "CONSUMABLE"){
			makeConsumableComponent(entity);
		} else if (component == "STARTING ITEMS"){
			parseStartingItems(stats, entity, entities);
		}
	}
}

void EntityFactory::makeEntity(std::string entityName, GameObject* entity, int x, int y, std::map<int, GameObject*> *entities)
{
	std::vector<std::string> components;
	
	if (m_mobs.find(entityName) != m_mobs.end()){
		components = m_mobs.at(entityName);
	}

	if (m_items.find(entityName) != m_items.end()){
		components = m_items.at(entityName);
	}

	if (m_player.find(entityName) != m_player.end()){
		components = m_player.at(entityName);
	}

	entity->m_name = entityName;
	entity->m_uid = m_uid;
	++m_uid;


	std::string component;
	std::string stats;

	for (std::string s : components){
		component = s.substr(0, s.find(":"));
		stats = s.substr(s.find(":")+1, s.length());
		if (component == "RENDERABLE"){
			makeRenderableComponent(stats, entity);
		} else if (component == "FIGHTER"){
			makeFighterComponent(stats, entity);
		} else if (component ==  "ACTOR"){
			makeActorComponent(entity);
		} else if (component ==  "AI"){
			makeAIComponent(stats, entity);
		} else if (component == "PLAYER"){
			makePlayerComponent(entity);
		} else if (component ==  "ITEM"){
			makeItemComponent(stats, entity);
		} else if (component == "WEAPON"){
			makeWeaponComponent(stats, entity);
		} else if (component ==  "ARMOUR"){
			makeArmourComponent(stats, entity);
		} else if (component ==  "WEARABLE"){
			makeWearableComponent(stats, entity);
		} else if (component ==  "BODY"){
			makeBodyComponent(entity);
		} else if (component == "INVENTORY"){
			makeInventoryComponent(s, entity);
		} else if (component == "USEABLE"){
			makeUseableComponent(stats, entity);
		} else if (component == "HEALING"){
			makeHealingComponent(stats, entity);
		} else if (component == "DIRECTDAMAGE"){
			makeDamageComponent(stats, entity);
		} else if (component == "AREADAMAGE"){
			makeAreaDamageComponent(stats, entity);
		} else if (component == "STATUS"){
			makeStatusComponent(stats, entity);
		} else if (component == "CONSUMABLE"){
			makeConsumableComponent(entity);
		} else if (component == "STARTING ITEMS"){
			parseStartingItems(stats, entity, entities);
		}
	}

	Position* p = new Position(x, y);
	entity->position = p;
}

void EntityFactory::makeEntity(int level, EntityType type, GameObject* entity, int x, int y, std::map<int, GameObject*> *entities)
{
	std::string entityName;

	if (type == PLAYERENTITY){
		entityName = "PLAYER";
	} else if (type == MOBENTITY){
		entityName = chooseRandomMob(level);
	} else if (type == ITEMENTITY){
		entityName = chooseRandomItem(level);
	}

	std::vector<std::string> components;
	
	if (m_mobs.find(entityName) != m_mobs.end()){
		components = m_mobs.at(entityName);
	}

	if (m_items.find(entityName) != m_items.end()){
		components = m_items.at(entityName);
	}

	if (m_player.find(entityName) != m_player.end()){
		components = m_player.at(entityName);
	}

	entity->m_name = entityName;
	entity->m_uid = m_uid;
	++m_uid;

	std::string component;
	std::string stats;

	for (std::string s : components){
		component = s.substr(0, s.find(":"));
		stats = s.substr(s.find(":")+1, s.length());
		if (component == "RENDERABLE"){
			makeRenderableComponent(stats, entity);
		} else if (component == "FIGHTER"){
			makeFighterComponent(stats, entity);
		} else if (component ==  "ACTOR"){
			makeActorComponent(entity);
		} else if (component ==  "AI"){
			makeAIComponent(stats, entity);
		} else if (component == "PLAYER"){
			makePlayerComponent(entity);
		} else if (component ==  "ITEM"){
			makeItemComponent(stats, entity);
		} else if (component == "WEAPON"){
			makeWeaponComponent(stats, entity);
		} else if (component ==  "ARMOUR"){
			makeArmourComponent(stats, entity);
		} else if (component ==  "WEARABLE"){
			makeWearableComponent(stats, entity);
		} else if (component ==  "BODY"){
			makeBodyComponent(entity);
		} else if (component == "INVENTORY"){
			makeInventoryComponent(s, entity);
		} else if (component == "USEABLE"){
			makeUseableComponent(stats, entity);
		} else if (component == "HEALING"){
			makeHealingComponent(stats, entity);
		} else if (component == "DIRECTDAMAGE"){
			makeDamageComponent(stats, entity);
		} else if (component == "AREADAMAGE"){
			makeAreaDamageComponent(stats, entity);
		} else if (component == "STATUS"){
			makeStatusComponent(stats, entity);
		} else if (component == "CONSUMABLE"){
			makeConsumableComponent(entity);
		} else if (component == "STARTING ITEMS"){
			parseStartingItems(stats, entity, entities);
		}
	}
	Position* p = new Position(x, y);
	entity->position = p;
}

void EntityFactory::makeStairs(GameObject* entity, int x, int y)
{
	std::string line = "< 0xef 0xd8 0xa1";
	makePositionComponent(entity, x, y);
	makeRenderableComponent(line, entity);
	Stairs *stairs = new Stairs();

	entity->stairs = stairs;
	entity->m_name = "stairs";
	entity->m_uid = m_uid;
	++m_uid;
}

