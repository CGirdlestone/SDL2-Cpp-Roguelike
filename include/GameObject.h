#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <string>

#include "Components.h"

class GameObject
{
public:
	GameObject();
  ~GameObject();

  std::string m_name;
	int m_uid;
  
	Position *position;
  Renderable *renderable;
  Fighter *fighter;
  Actor *actor;
  Player *player;
  AI *ai;
  Item *item;
  Inventory *inventory;
  Weapon *weapon;
  Armour *armour;
  Wearable *wearable;
  Body *body;
	Useable *useable;
	Healing *healing;
	Damage *damage;
	AreaDamage *areaDamage;
	Status *status;
	Consumable *consumable;

protected:

private:
};

#endif
