
#include "SDL2/SDL.h"

#include "Components.h"
#include <string>

void serialiseInt(std::vector<uint8_t> &byteVector, int x)
{
	byteVector.push_back(static_cast<unsigned int>(x) & 0xFF);
	byteVector.push_back((static_cast<unsigned int>(x) >> 8) & 0xFF);
	byteVector.push_back((static_cast<unsigned int>(x) >> 16) & 0xFF);
	byteVector.push_back((static_cast<unsigned int>(x) >> 24) & 0xFF);
}

void serialiseString(std::vector<uint8_t> &byteVector, std::string stringToSerialise)
{
	int size = stringToSerialise.length();
	int letterCode;

	serialiseInt(byteVector, size);
	
	for (int i = 0; i < size; ++i){
		letterCode = static_cast<int>(stringToSerialise[i]);
		serialiseInt(byteVector, letterCode);
	}
}

int deserialiseInt(char* buffer, int& i)
{
	int numBytes = 4;
	int value = 0;

	for (int j = numBytes - 1; j >= 0; --j){
		value = (value << 8) + buffer[i + j];
	}
	i += numBytes * 8;

	return value;
}

Position::Position(int i, int j)
{
  x = i;
  y = j;
}

Position::Position()
{
	x = 0;
	y = 0;
}

Position::~Position()
{

}

void Position::serialise(std::vector<uint8_t> &byteVector)
{
	serialiseInt(byteVector, x);
	serialiseInt(byteVector, y);
}

int Position::deserialise(char* buffer, int i)
{
	x = deserialiseInt(buffer, i);
	y = deserialiseInt(buffer, i);

	return i;
}


Renderable::Renderable(char _chr, SDL_Color _colour, int _spriteX, int _spriteY, int _sheet)
{
  chr = _chr;
  colour = _colour;
	spriteX = _spriteX;
	spriteY = _spriteY;
	sheet = _sheet;
}

Renderable::Renderable()
{

}

Renderable::~Renderable()
{

}

void Renderable::serialise(std::vector<uint8_t> &byteVector)
{
	serialiseInt(byteVector, static_cast<int>(chr));
	serialiseInt(byteVector, colour.r);
	serialiseInt(byteVector, colour.g);
	serialiseInt(byteVector, colour.b);
	serialiseInt(byteVector, spriteX);
	serialiseInt(byteVector, spriteY);
	serialiseInt(byteVector, sheet);
}

int Renderable::deserialise(char* buffer, int i)
{
	int red = 0;
	int green = 0;
	int blue = 0;

	chr = deserialiseInt(buffer, i);
	red = deserialiseInt(buffer, i);	
	green = deserialiseInt(buffer, i);	
	blue = deserialiseInt(buffer, i);	
	
	colour = {red, green, blue};

	spriteX = deserialiseInt(buffer, i);
	spriteY = deserialiseInt(buffer, i);
	sheet = deserialiseInt(buffer, i);

	return i;
}


Fighter::Fighter(int _maxHealth, int _power, int _defence):
maxHealth(_maxHealth), health(_maxHealth), power(_power), defence(_defence), isAlive(true)
{

}

Fighter::Fighter()
{
	health = 0;
	maxHealth = 0;
	power = 0;
	defence = 0;
	isAlive = true;
}

Fighter::~Fighter()
{

}

void Fighter::serialise(std::vector<uint8_t> &byteVector)
{
	int _isAlive = 1;

	serialiseInt(byteVector, health);
	serialiseInt(byteVector, maxHealth);
	serialiseInt(byteVector, power);
	serialiseInt(byteVector, defence);
	serialiseInt(byteVector, _isAlive);
}

int Fighter::deserialise(char* buffer, int i)
{
	health = deserialiseInt(buffer, i);
	maxHealth = deserialiseInt(buffer, i);
	power = deserialiseInt(buffer, i);
	defence = deserialiseInt(buffer, i);
	isAlive = deserialiseInt(buffer, i) == 1 ? true : false;

	return i;
}

Actor::Actor()
{

}

Actor::~Actor()
{

}

void Actor::serialise(std::vector<uint8_t> &byteVector)
{

}

int Actor::deserialise(char* buffer, int i)
{

	return i;
}


Player::Player()
{
	level = 1;
	exp = 0;
	next = 100;
}

Player::~Player()
{

}
#include <stdio.h>
void Player::serialise(std::vector<uint8_t> &byteVector)
{
	serialiseInt(byteVector, level);
	serialiseInt(byteVector, exp);
	serialiseInt(byteVector, next);
}

int Player::deserialise(char* buffer, int i)
{
	level = deserialiseInt(buffer, i);
	exp = deserialiseInt(buffer, i);
	next = deserialiseInt(buffer, i);

	return i;
}


Item::Item(std::string desc, int _level):
description(desc), level(_level)
{

}

Item::Item()
{
	description = "";
}

Item::~Item()
{

}

void Item::serialise(std::vector<uint8_t> &byteVector)
{
	serialiseString(byteVector, description);
	serialiseInt(byteVector, level);
}

int Item::deserialise(char* buffer, int i)
{
	int descLength = deserialiseInt(buffer, i);

	char* desc = new char[descLength];
	for (int k = 0; k < descLength; ++k){
		desc[k] = static_cast<char>(deserialiseInt(buffer, i));
	}
	description.assign(desc, descLength);

	delete[] desc;

	level = deserialiseInt(buffer, i);

	return i;
}

AI::AI(int _exp, int _level):
exp(_exp), level(_level)
{

}

AI::AI()
{
	exp = 0;
}

AI::~AI()
{

}

void AI::serialise(std::vector<uint8_t> &byteVector)
{
	serialiseInt(byteVector, exp);
	serialiseInt(byteVector, level);
}

int AI::deserialise(char* buffer, int i)
{
	exp = deserialiseInt(buffer, i);
	level = deserialiseInt(buffer, i);

	return i;
}

Inventory::Inventory(int _capacity):
capacity(_capacity)
{

}

Inventory::Inventory()
{
	capacity = 0;
}

Inventory::~Inventory()
{

}

void Inventory::serialise(std::vector<uint8_t> &byteVector)
{
	int inventorySize = static_cast<int>(inventory.size());

	serialiseInt(byteVector, capacity);
	serialiseInt(byteVector, inventorySize);
	for (int i = 0; i < inventorySize; ++i){
		serialiseInt(byteVector, inventory.at(i)->m_uid);
	}
}

int Inventory::deserialise(char* buffer, int i)
{
	capacity = deserialiseInt(buffer, i);

	int inventorySize = deserialiseInt(buffer, i);	
	
	for (int k = 0; k < inventorySize; ++k){
		inventoryMirror.push_back(deserialiseInt(buffer, i));
	}

	return i;
}


Weapon::Weapon(DamageTypes _damageType, int _sidedDie, bool _twoHanded):
damageType(_damageType), sidedDie(_sidedDie), twoHanded(_twoHanded)
{

}

Weapon::Weapon()
{
	sidedDie = 0;
	twoHanded = false;
}

Weapon::~Weapon()
{

}

void Weapon::serialise(std::vector<uint8_t> &byteVector)
{
	serialiseInt(byteVector, static_cast<int>(damageType));
	serialiseInt(byteVector, sidedDie);
	serialiseInt(byteVector, static_cast<int>(twoHanded));
}

int Weapon::deserialise(char* buffer, int i)
{
	damageType = static_cast<DamageTypes>(deserialiseInt(buffer, i));
	sidedDie = deserialiseInt(buffer, i);
	twoHanded = deserialiseInt(buffer, i);
	
	return i;
}

Armour::Armour(DamageTypes _resistance, DamageTypes _weakness, int _armourBonus):
resistance(_resistance), weakness(_weakness), armourBonus(_armourBonus)
{

}

Armour::Armour()
{

}

Armour::~Armour()
{

}

void Armour::serialise(std::vector<uint8_t> &byteVector)
{
	serialiseInt(byteVector, static_cast<int>(resistance));
	serialiseInt(byteVector, static_cast<int>(weakness));
	serialiseInt(byteVector, armourBonus);
}

int Armour::deserialise(char* buffer, int i)
{
	resistance = static_cast<DamageTypes>(deserialiseInt(buffer, i));
	weakness = static_cast<DamageTypes>(deserialiseInt(buffer, i));
	armourBonus = deserialiseInt(buffer, i);

	return i;
}


Wearable::Wearable(EquipSlots _slot):
slot(_slot)
{

}

Wearable::Wearable()
{

}

Wearable::~Wearable()
{

}

void Wearable::serialise(std::vector<uint8_t> &byteVector)
{
	serialiseInt(byteVector, static_cast<int>(slot));
}

int Wearable::deserialise(char* buffer, int i)
{
	slot = static_cast<EquipSlots>(deserialiseInt(buffer, i));

	return i;
}


Body::Body()
{
  slots.insert({HEAD, nullptr});
  slots.insert({LEFTHAND, nullptr});
  slots.insert({RIGHTHAND, nullptr});
  slots.insert({BODY, nullptr});
  slots.insert({NECK, nullptr});
  slots.insert({BACK, nullptr});
}

Body::~Body()
{

}

void Body::serialise(std::vector<uint8_t> &byteVector)
{
	std::map<EquipSlots, GameObject*>::iterator it;
	int empty = 0;

	for (it = slots.begin(); it != slots.end(); ++it){
		serialiseInt(byteVector, static_cast<int>(it->first));
		if (it->second != nullptr){
			serialiseInt(byteVector, it->second->m_uid);
		} else {
			serialiseInt(byteVector, empty);
		}
	}
}

int Body::deserialise(char* buffer, int i)
{
	int headKey = 0;
	int headValue = 0;
	int leftKey = 0;
	int leftValue = 0;
	int rightKey = 0;
	int rightValue = 0;
	int bodyKey = 0;
	int bodyValue = 0;
	int neckKey = 0;
	int neckValue = 0;
	int backKey = 0;
	int backValue = 0;

	
	headKey = deserialiseInt(buffer, i);
	headValue = deserialiseInt(buffer, i);
	leftKey = deserialiseInt(buffer, i);
	leftValue = deserialiseInt(buffer, i);
	rightKey = deserialiseInt(buffer, i);
	rightValue = deserialiseInt(buffer, i);
	bodyKey = deserialiseInt(buffer, i);
	bodyValue = deserialiseInt(buffer, i);
	neckKey = deserialiseInt(buffer, i);
	neckValue = deserialiseInt(buffer, i);
	backKey = deserialiseInt(buffer, i);
	backValue = deserialiseInt(buffer, i);

	slotsMirror.insert({headKey, headValue});
	slotsMirror.insert({leftKey, leftValue});
	slotsMirror.insert({rightKey, rightValue});
	slotsMirror.insert({bodyKey, bodyValue});
	slotsMirror.insert({neckKey, neckValue});
	slotsMirror.insert({backKey, backValue});

	return i;
}


Useable::Useable(UseableFunctionEnums func, int _numUses):
funcToDo(func), numUses(_numUses)
{

}

Useable::Useable()
{
	numUses = 0;
}

Useable::~Useable()
{

}

void Useable::serialise(std::vector<uint8_t> &byteVector)
{
	serialiseInt(byteVector, static_cast<int>(funcToDo));
	serialiseInt(byteVector, numUses);
}

int Useable::deserialise(char* buffer, int i)
{
	funcToDo = static_cast<UseableFunctionEnums>(deserialiseInt(buffer, i));
	numUses = deserialiseInt(buffer, i);

	return i;
}


Healing::Healing(int _roll):
roll(_roll)
{

}

Healing::Healing()
{
	roll = 0;
}

Healing::~Healing()
{

}

void Healing::serialise(std::vector<uint8_t> &byteVector)
{
	serialiseInt(byteVector, roll);
}

int Healing::deserialise(char* buffer, int i)
{
	roll = deserialiseInt(buffer, i);

	return i;
}

Damage::Damage(int _radius, int _roll, DamageTypes _type, int _chance):
radius(_radius), roll(_roll), type(_type), chance(_chance)
{

}

Damage::Damage()
{
	radius = 0;
	roll = 0;
	chance = 0;
}

Damage::~Damage()
{

}

void Damage::serialise(std::vector<uint8_t> &byteVector)
{
	serialiseInt(byteVector, radius);
	serialiseInt(byteVector, roll);
	serialiseInt(byteVector, static_cast<int>(type));
	serialiseInt(byteVector, chance);
}

int Damage::deserialise(char* buffer, int i)
{
	radius = deserialiseInt(buffer, i);
	roll = deserialiseInt(buffer, i);
	type = static_cast<DamageTypes>(deserialiseInt(buffer, i));
	chance = deserialiseInt(buffer, i);

	return i;
}


AreaDamage::AreaDamage(int _radius, int _roll, int _splashRadius, DamageTypes _type, int _chance):
radius(_radius), roll(_roll), splashRadius(_splashRadius), type(_type), chance(_chance)
{

}

AreaDamage::AreaDamage()
{

}

AreaDamage::~AreaDamage()
{

}

void AreaDamage::serialise(std::vector<uint8_t> &byteVector)
{
	serialiseInt(byteVector, radius);
	serialiseInt(byteVector, roll);
	serialiseInt(byteVector, splashRadius);
	serialiseInt(byteVector, static_cast<int>(type));
	serialiseInt(byteVector, chance);
}

int AreaDamage::deserialise(char* buffer, int i)
{
	radius = deserialiseInt(buffer, i);
	roll = deserialiseInt(buffer, i);
	splashRadius = deserialiseInt(buffer, i);
	type = static_cast<DamageTypes>(deserialiseInt(buffer, i));
	chance = deserialiseInt(buffer, i);

	return i;
}


Status::Status(int _radius, StatusTypes _status, int _splashRadius):
radius(_radius), statusType(_status), splashRadius(_splashRadius)
{

}

Status::Status()
{
	radius = 0;
	splashRadius = 0;
}

Status::~Status()
{

}

void Status::serialise(std::vector<uint8_t> &byteVector)
{
	serialiseInt(byteVector, radius);
	serialiseInt(byteVector, static_cast<int>(statusType));
	serialiseInt(byteVector, splashRadius);
}

int Status::deserialise(char* buffer, int i)
{
	radius = deserialiseInt(buffer, i);
	statusType = static_cast<StatusTypes>(deserialiseInt(buffer, i));
	splashRadius = deserialiseInt(buffer, i);

	return i;
}


Consumable::Consumable()
{

}

Consumable::~Consumable()
{

}

void Consumable::serialise(std::vector<uint8_t> &byteVector)
{

}

int Consumable::deserialise(char* buffer, int i)
{
	return i;
}

Stairs::Stairs()
{

}

Stairs::~Stairs()
{

}

void Stairs::serialise(std::vector<uint8_t> &byteVector)
{

}

int Stairs::deserialise(char* buffer, int i)
{
	return i;
}

StatusContainer::StatusContainer()
{
	for (int i = 0; i <= static_cast<int>(BLEEDING); ++i){
		statuses.insert({static_cast<StatusTypes>(i), std::make_pair(0, 0)}); // pair<damage, duration>
	}
}

StatusContainer::~StatusContainer()
{
}

void StatusContainer::serialise(std::vector<uint8_t> &byteVector)
{
	for (int i = 0; i <= static_cast<int>(BLEEDING); ++i){
		serialiseInt(byteVector, std::get<0>(statuses.at(static_cast<StatusTypes>(i))));
		serialiseInt(byteVector, std::get<1>(statuses.at(static_cast<StatusTypes>(i))));
	}
}

int StatusContainer::deserialise(char* buffer, int i)
{
	for (int k = 0; k <= static_cast<int>(BLEEDING); ++k){	
		statuses.at(static_cast<StatusTypes>(k)).first = deserialiseInt(buffer, i);
		statuses.at(static_cast<StatusTypes>(k)).second = deserialiseInt(buffer, i);
	}

	return i;
}
