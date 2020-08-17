
#include "GameObject.h"
#include "Components.h"
#include <string>
#include <vector>
#include <iostream>

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
	statusContainer = nullptr;
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

	if(statusContainer != nullptr){
		delete statusContainer;
		statusContainer = nullptr;
	}
}

void GameObject::serialise(std::vector<uint8_t> &byteVector)
{
	serialiseInt(byteVector, m_uid);

	serialiseString(byteVector, m_name);

	if (position == nullptr){
		serialiseInt(byteVector, 0);
	} else {
		serialiseInt(byteVector, 1);
		position->serialise(byteVector);
	}

	if (renderable == nullptr){
		serialiseInt(byteVector, 0);
	} else {
		serialiseInt(byteVector, 1);
		renderable->serialise(byteVector);
	}

	if (fighter == nullptr){
		serialiseInt(byteVector, 0);
	} else {
		serialiseInt(byteVector, 1);
		fighter->serialise(byteVector);
	}

	if (actor == nullptr){
		serialiseInt(byteVector, 0);
	} else {
		serialiseInt(byteVector, 1);
		actor->serialise(byteVector);
	}

	if (player == nullptr){
		serialiseInt(byteVector, 0);
	} else {
		serialiseInt(byteVector, 1);
		player->serialise(byteVector);
	}

	if (ai == nullptr){
		serialiseInt(byteVector, 0);
	} else {
		serialiseInt(byteVector, 1);
		ai->serialise(byteVector);
	}

	if (item == nullptr){
		serialiseInt(byteVector, 0);
	} else {
		serialiseInt(byteVector, 1);
		item->serialise(byteVector);
	}

	if (inventory == nullptr){
		serialiseInt(byteVector, 0);
	} else {
		serialiseInt(byteVector, 1);
		inventory->serialise(byteVector);
	}

	if (weapon == nullptr){
		serialiseInt(byteVector, 0);
	} else {
		serialiseInt(byteVector, 1);
		weapon->serialise(byteVector);
	}

	if (armour == nullptr){
		serialiseInt(byteVector, 0);
	} else {
		serialiseInt(byteVector, 1);
		armour->serialise(byteVector);
	}

	if (wearable == nullptr){
		serialiseInt(byteVector, 0);
	} else {
		serialiseInt(byteVector, 1);
		wearable->serialise(byteVector);
	}

	if (body == nullptr){
		serialiseInt(byteVector, 0);
	} else {
		serialiseInt(byteVector, 1);
		body->serialise(byteVector);
	}

	if (useable == nullptr){
		serialiseInt(byteVector, 0);
	} else {
		serialiseInt(byteVector, 1);
		useable->serialise(byteVector);
	}

	if (healing == nullptr){
		serialiseInt(byteVector, 0);
	} else {
		serialiseInt(byteVector, 1);
		healing->serialise(byteVector);
	}

	if (damage == nullptr){
		serialiseInt(byteVector, 0);
	} else {
		serialiseInt(byteVector, 1);
		damage->serialise(byteVector);
	}

	if (areaDamage == nullptr){
		serialiseInt(byteVector, 0);
	} else {
		serialiseInt(byteVector, 1);
		areaDamage->serialise(byteVector);
	}

	if (status == nullptr){
		serialiseInt(byteVector, 0);
	} else {
		serialiseInt(byteVector, 1);
		status->serialise(byteVector);
	}

	if (consumable == nullptr){
		serialiseInt(byteVector, 0);
	} else {
		serialiseInt(byteVector, 1);
		consumable->serialise(byteVector);
	}

	if (stairs == nullptr){
		serialiseInt(byteVector, 0);
	} else {
		serialiseInt(byteVector, 1);
		stairs->serialise(byteVector);
	}

	if (statusContainer == nullptr){
		serialiseInt(byteVector, 0);
	} else {
		serialiseInt(byteVector, 1);
		statusContainer->serialise(byteVector);
	}
}

int GameObject::deserialise(char* buffer, int i)
{
	int numBytes = 4;
	int hasPointer = 0;
	int _uid;
	int _nameLength;

	/* Read in the entity's uid */
	for (int j = numBytes - 1; j >= 0; --j){
		_uid = (_uid << 8) + buffer[i + j];
	}
	m_uid = _uid;
	i += numBytes * 8;

	/* Read in the bytes holding the length of the entity's name */
	for (int j = numBytes - 1; j >= 0; --j){
		_nameLength = (_nameLength << 8) + buffer[i + j];
	}
	i += numBytes * 8;

	/* Read in the entity's name */
	char* name = new char[_nameLength];
	int letterCode;
	for (int k = 0; k < _nameLength; ++k){
		letterCode = 0;
		for (int j = numBytes - 1; j >= 0; --j){
			letterCode = (letterCode << 8) + buffer[i + j];
		}
		i += numBytes * 8;
		name[k] = static_cast<char>(letterCode);
	}
	m_name.assign(name, _nameLength);
	delete[] name;

	/* Read in the entity's components. The first set of 4 bytes denotes whether the pointer is valid (1) or nullptr (0). */
	for (int j = numBytes - 1; j >= 0; --j){
		hasPointer = (hasPointer << 8) + buffer[i+j]; 
	}
	i += numBytes * 8;

	if (hasPointer == 1){
		position = new Position();
		i = position->deserialise(buffer, i);
		hasPointer = 0;
	}
	
	for (int j = numBytes - 1; j >= 0; --j){
		hasPointer = (hasPointer << 8) + buffer[i+j]; 
	}
	i += numBytes * 8;

	if (hasPointer == 1){
		renderable = new Renderable();
		i = renderable->deserialise(buffer, i);
		hasPointer = 0;
	}
	
	for (int j = numBytes - 1; j >= 0; --j){
		hasPointer = (hasPointer << 8) + buffer[i+j]; 
	}
	i += numBytes * 8;

	if (hasPointer == 1){
		fighter = new Fighter();
		i = fighter->deserialise(buffer, i);
		hasPointer = 0;
	}
	
	for (int j = numBytes - 1; j >= 0; --j){
		hasPointer = (hasPointer << 8) + buffer[i+j]; 
	}
	i += numBytes * 8;

	if (hasPointer == 1){
		actor = new Actor();
		i = actor->deserialise(buffer, i);
		hasPointer = 0;
	}
	
	for (int j = numBytes - 1; j >= 0; --j){
		hasPointer = (hasPointer << 8) + buffer[i+j]; 
	}
	i += numBytes * 8;

	if (hasPointer == 1){
		player = new Player();
		i = player->deserialise(buffer, i);
		hasPointer = 0;
	}
	
	for (int j = numBytes - 1; j >= 0; --j){
		hasPointer = (hasPointer << 8) + buffer[i+j]; 
	}
	i += numBytes * 8;

	if (hasPointer == 1){
		ai = new AI();
		i = ai->deserialise(buffer, i);
		hasPointer = 0;
	}
	
	for (int j = numBytes - 1; j >= 0; --j){
		hasPointer = (hasPointer << 8) + buffer[i+j]; 
	}
	i += numBytes * 8;

	if (hasPointer == 1){
		item = new Item();
		i = item->deserialise(buffer, i);
		hasPointer = 0;
	}
	
	for (int j = numBytes - 1; j >= 0; --j){
		hasPointer = (hasPointer << 8) + buffer[i+j]; 
	}
	i += numBytes * 8;

	if (hasPointer == 1){
		inventory = new Inventory();
		i = inventory->deserialise(buffer, i);
		hasPointer = 0;
	}
	
	for (int j = numBytes - 1; j >= 0; --j){
		hasPointer = (hasPointer << 8) + buffer[i+j]; 
	}
	i += numBytes * 8;

	if (hasPointer == 1){
		weapon = new Weapon();
		i = weapon->deserialise(buffer, i);
		hasPointer = 0;
	}
	
	for (int j = numBytes - 1; j >= 0; --j){
		hasPointer = (hasPointer << 8) + buffer[i+j]; 
	}
	i += numBytes * 8;

	if (hasPointer == 1){
		armour = new Armour();
		i = armour->deserialise(buffer, i);
		hasPointer = 0;
	}
	
	for (int j = numBytes - 1; j >= 0; --j){
		hasPointer = (hasPointer << 8) + buffer[i+j]; 
	}
	i += numBytes * 8;

	if (hasPointer == 1){
		wearable = new Wearable();
		i = wearable->deserialise(buffer, i);
		hasPointer = 0;
	}
	
	for (int j = numBytes - 1; j >= 0; --j){
		hasPointer = (hasPointer << 8) + buffer[i+j]; 
	}
	i += numBytes * 8;

	if (hasPointer == 1){
		body = new Body();
		i = body->deserialise(buffer, i);
		hasPointer = 0;
	}
	
	for (int j = numBytes - 1; j >= 0; --j){
		hasPointer = (hasPointer << 8) + buffer[i+j]; 
	}
	i += numBytes * 8;

	if (hasPointer == 1){
		useable = new Useable();
		i = useable->deserialise(buffer, i);
		hasPointer = 0;
	}
	
	for (int j = numBytes - 1; j >= 0; --j){
		hasPointer = (hasPointer << 8) + buffer[i+j]; 
	}
	i += numBytes * 8;

	if (hasPointer == 1){
		healing = new Healing();
		i = healing->deserialise(buffer, i);
		hasPointer = 0;
	}
	
	for (int j = numBytes - 1; j >= 0; --j){
		hasPointer = (hasPointer << 8) + buffer[i+j]; 
	}
	i += numBytes * 8;

	if (hasPointer == 1){
		damage = new Damage();
		i = damage->deserialise(buffer, i);
		hasPointer = 0;
	}
	
	for (int j = numBytes - 1; j >= 0; --j){
		hasPointer = (hasPointer << 8) + buffer[i+j]; 
	}
	i += numBytes * 8;

	if (hasPointer == 1){
		areaDamage = new AreaDamage();
		i = areaDamage->deserialise(buffer, i);
		hasPointer = 0;
	}
	
	for (int j = numBytes - 1; j >= 0; --j){
		hasPointer = (hasPointer << 8) + buffer[i+j]; 
	}
	i += numBytes * 8;

	if (hasPointer == 1){
		status = new Status();
		i = status->deserialise(buffer, i);
		hasPointer = 0;
	}
	
	for (int j = numBytes - 1; j >= 0; --j){
		hasPointer = (hasPointer << 8) + buffer[i+j]; 
	}
	i += numBytes * 8;

	if (hasPointer == 1){
		consumable = new Consumable();
		i = consumable->deserialise(buffer, i);
		hasPointer = 0;
	}
	
	for (int j = numBytes - 1; j >= 0; --j){
		hasPointer = (hasPointer << 8) + buffer[i+j]; 
	}
	i += numBytes * 8;

	if (hasPointer == 1){
		stairs = new Stairs();
		i = stairs->deserialise(buffer, i);
		hasPointer = 0;
	}
	
	for (int j = numBytes - 1; j >= 0; --j){
		hasPointer = (hasPointer << 8) + buffer[i+j]; 
	}
	i += numBytes * 8;

	if (hasPointer == 1){
		statusContainer = new StatusContainer();
		i = statusContainer->deserialise(buffer, i);
		hasPointer = 0;
	}
	return i;
}



