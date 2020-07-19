
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

DamageTypes EntityFactory::getDamageTypeEnum(std::string stringEnum)
{
	if (stringEnum == "SLASHING"){
		return SLASHING;
	} else if (stringEnum == "PIERCING"){
		return PIERCING;
	} else if (stringEnum == "BLUDGEONING"){
		return BLUDGEONING;
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
	} else if (stringEnum == "DAMAGE"){
		return DIRECTDAMAGE;
	} else if (stringEnum == "AREA DAMAGE"){
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
	Item* item = new Item(line);

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

	ss >> resistanceString >> weaknessString;
	resistanceEnum = getDamageTypeEnum(resistanceString);
	weaknessEnum = getDamageTypeEnum(weaknessString);

	Armour* armour = new Armour(resistanceEnum, weaknessEnum);

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

void EntityFactory::makeAIComponent(GameObject* entity)
{
	AI* ai = new AI();

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

}

void EntityFactory::makeAreaDamageComponent(std::string line, GameObject* entity)
{

}

void EntityFactory::makeStatusComponent(std::string line, GameObject* entity)
{

}

void EntityFactory::makeConsumableComponent(GameObject* entity)
{
	Consumable* c = new Consumable();

	entity->consumable = c;
}

void EntityFactory::makeEntity(std::string entityName, GameObject* entity, int x, int y)
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

	std::string component;
	std::string stats;

	for (std::string s : components){
		component = s.substr(0, s.find(":"));
		stats = s.substr(s.find(":")+1, s.length());
		if (component == "RENDERABLE"){
			makeRenderableComponent(stats, entity);
		} else if (component == "POSITION"){
			makePositionComponent(entity, x, y);
		} else if (component == "FIGHTER"){
			makeFighterComponent(stats, entity);
		} else if (component ==  "ACTOR"){
			makeActorComponent(entity);
		} else if (component ==  "AI"){
			makeAIComponent(entity);
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
		} else if (component == "DAMAGE"){
			makeDamageComponent(stats, entity);
		} else if (component == "AREADAMAGE"){
			makeAreaDamageComponent(stats, entity);
		} else if (component == "STATUS"){
			makeStatusComponent(stats, entity);
		} else if (component == "CONSUMABLE"){
			makeConsumableComponent(entity);
		}
	}

	entity->m_name = entityName;
	entity->m_uid = m_uid;
	++m_uid;
}

