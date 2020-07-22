#ifndef ENTITYFACTORY_H
#define ENTITYFACTORY_H

#include<map>
#include<vector>
#include<string>

#include "GameObject.h"
#include "DamageTypes.h"
#include "Slots.h"
#include "UseableFunctionEnum.h"

class EntityFactory
{
public:
	EntityFactory();
	~EntityFactory();
	void makeRenderableComponent(std::string line, GameObject* entity);
	void makeFighterComponent(std::string line, GameObject* entity);
	void makeItemComponent(std::string line, GameObject* entity);
	void makeWeaponComponent(std::string line, GameObject* entity);
	void makeArmourComponent(std::string line, GameObject* entity);
	void makeAIComponent(std::string line, GameObject* entity);
	void makeActorComponent(GameObject* entity);
	void makeInventoryComponent(std::string line, GameObject* entity);
	void makePositionComponent(GameObject* entity, int x, int y);
	void makeBodyComponent(GameObject* entity);
	void makeWearableComponent(std::string line, GameObject* entity);
	void makePlayerComponent(GameObject* entity);
	void makeUseableComponent(std::string line, GameObject* entity);
	void makeHealingComponent(std::string line, GameObject* entity);
	void makeDamageComponent(std::string line, GameObject* entity);
	void makeAreaDamageComponent(std::string line, GameObject* entity);
	void makeStatusComponent(std::string line, GameObject* entity);
	void makeConsumableComponent(GameObject* entity);

	DamageTypes getDamageTypeEnum(std::string stringEnum);
	EquipSlots getEquipSlotEnum(std::string stringEnum);
	UseableFunctionEnums getFunctionEnum(std::string stringEnum);
	
	void loadData(std::string filename);

	void makeEntity(std::string entityName, GameObject* entity, int x, int y);
	void makeStairs(GameObject* entity, int x, int y);

private:
	int m_uid;
	std::map<std::string, std::vector<std::string>> m_items;
	std::map<std::string, std::vector<std::string>> m_mobs;
	std::map<std::string, std::vector<std::string>> m_player;
};

#endif
