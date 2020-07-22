
#include "GameObject.h"
#include <string>
#include <vector>

GameObject::GameObject()
{
  position = nullptr;
  renderable = nullptr;
  fighter = nullptr;
  actor = nullptr;
  player = nullptr;
  ai = nullptr;
  item = nullptr;
  inventory = nullptr;
  weapon = nullptr;
  armour = nullptr;
  wearable = nullptr;
  body = nullptr;
	useable = nullptr;
	healing = nullptr;
	damage = nullptr;
	areaDamage = nullptr;
	status = nullptr;
	consumable = nullptr;
	stairs = nullptr;
}

GameObject::~GameObject()
{
  if(position != nullptr){
    delete position;
    position = nullptr;
  }

  if(renderable != nullptr){
    delete renderable;
    renderable = nullptr;
  }

  if(fighter != nullptr){
    delete fighter;
    fighter = nullptr;
  }

  if(actor != nullptr){
    delete actor;
    actor = nullptr;
  }

  if(player != nullptr){
    delete player;
    player = nullptr;
  }

  if(ai != nullptr){
    delete ai;
    ai = nullptr;
  }

  if(item != nullptr){
    delete item;
    item = nullptr;
  }

  if(inventory != nullptr){
    delete inventory;
    inventory = nullptr;
  }

  if(weapon != nullptr){
    delete weapon;
    weapon = nullptr;
  }

  if(armour != nullptr){
    delete armour;
    armour = nullptr;
  }

  if(wearable != nullptr){
    delete wearable;
    wearable = nullptr;
  }

  if(body != nullptr){
    delete body;
    body = nullptr;
  }
	
	if(useable != nullptr){
		delete useable;
		useable = nullptr;
	}

	if(healing != nullptr){
		delete healing;
		healing = nullptr;
	}

	if(damage != nullptr){
		delete damage;
		damage = nullptr;
	}

	if(areaDamage != nullptr){
		delete areaDamage;
		areaDamage = nullptr;
	}

	if(status != nullptr){
		delete status;
		status = nullptr;
	}

	if(consumable != nullptr){
		delete consumable;
		consumable = nullptr;
	}
	
	if(stairs != nullptr){
		delete stairs;
		stairs = nullptr;
	}
}
