
#include "SDL2/SDL.h"

#include "Components.h"
#include <string>

void serialiseInt(std::vector<uint8_t> &byteVector, int x)
{
	byteVector.push_back(x & 0xFF);
	byteVector.push_back((x << 8) & 0xFF);
	byteVector.push_back((x << 16) & 0xFF);
	byteVector.push_back((x << 24) & 0xFF);
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
	int numBytes = 4;
	int _x = 0;
	int _y = 0;

	for (int j = numBytes - 1; j >= 0; --j){
		_x = (_x << 8) + buffer[i + j];
	}
	x = _x;
	i += numBytes * 8;

	for (int j = numBytes - 1; j >= 0; --j){
		_y = (_y << 8) + buffer[i + j];
	}
	y = _y;
	i += numBytes * 8;

	return i;
}


Renderable::Renderable(char _chr, SDL_Color _colour)
{
    chr = _chr;
    colour = _colour;
}

Renderable::Renderable()
{
	chr = ' ';
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
}

int Renderable::deserialise(char* buffer, int i)
{
	int numBytes = 4;
	int _chr = 0;
	int _red = 0;
	int _green = 0;
	int _blue = 0;

	for (int j = numBytes - 1; j >= 0; --j){
		_chr = (_chr << 8) + buffer[i + j];
	}
	chr = static_cast<char>(_chr);
	i += numBytes * 8;
	
	for (int j = numBytes - 1; j >= 0; --j){
		_red = (_red << 8) + buffer[i + j];
	}
	i += numBytes * 8;
	
	for (int j = numBytes - 1; j >= 0; --j){
		_green = (_green << 8) + buffer[i + j];
	}
	i += numBytes * 8;

	for (int j = numBytes - 1; j >= 0; --j){
		_blue = (_blue << 8) + buffer[i + j];
	}
	i += numBytes * 8;

	colour = {_red, _green, _blue};

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
	int numBytes = 4;

	int _health = 0;
	int _maxHealth = 0;
	int _power = 0;
	int _defence = 0;
	int _isAlive = 0;	

	for (int j = numBytes - 1; j >= 0; --j){
		_health = (_health << 8) + buffer[i + j];
	}
	health = _health;
	i += numBytes * 8;

	for (int j = numBytes - 1; j >= 0; --j){
		_maxHealth = (_maxHealth << 8) + buffer[i + j];
	}
	maxHealth = _maxHealth;
	i += numBytes * 8;

	for (int j = numBytes - 1; j >= 0; --j){
		_power = (_power << 8) + buffer[i + j];
	}
	power = _power;
	i += numBytes * 8;

	for (int j = numBytes - 1; j >= 0; --j){
		_defence = (_defence << 8) + buffer[i + j];
	}
	defence = _defence;
	i += numBytes * 8;

	for (int j = numBytes - 1; j >= 0; --j){
		_isAlive = (_isAlive << 8) + buffer[i + j];
	}
	isAlive = _isAlive == 1 ? true : false;
	i += numBytes * 8;

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

void Player::serialise(std::vector<uint8_t> &byteVector)
{
	serialiseInt(byteVector, level);
	serialiseInt(byteVector, exp);
	serialiseInt(byteVector, next);
}

int Player::deserialise(char* buffer, int i)
{
	int numBytes = 4;

	int _level = 0;
	int _exp = 0;
	int _next = 0;

	for (int j = numBytes - 1; j >= 0; --j){
		_level = (_level << 8) + buffer[i + j];
	}
	level = _level;
	i += numBytes * 8;

	for (int j = numBytes - 1; j >= 0; --j){
		_exp = (_exp << 8) + buffer[i + j];
	}
	exp = _exp;
	i += numBytes * 8;

	for (int j = numBytes - 1; j >= 0; --j){
		_next = (_next << 8) + buffer[i + j];
	}
	next = _next;
	i += numBytes * 8;

	return i;
}


Item::Item(std::string desc):
description(desc)
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
}

int Item::deserialise(char* buffer, int i)
{
	int numBytes = 4;
	int descLength = 0;

	for (int j = numBytes - 1; j >= 0; --j){
		descLength = (descLength << 8) + buffer[i + j];
	}
	i += numBytes * 8;

	char* desc = new char[descLength];
	int letter;
	for (int k = 0; k < descLength; ++k){
		letter = 0;
		for (int j = numBytes - 1; j >= 0; --j){
			letter = (letter << 8) + buffer[i + j];
		}
		i += numBytes * 8;
		desc[k] = static_cast<char>(letter);
	}
	description.assign(desc, descLength);

	delete[] desc;

	return i;
}

AI::AI(int _exp):
exp(_exp)
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
}

int AI::deserialise(char* buffer, int i)
{
	int numBytes = 4;
	int _exp = 0;

	for (int j = numBytes - 1; j >= 0; --j){
		_exp = (_exp << 8) + buffer[i + j];
	}
	i += numBytes * 8;
	exp = _exp;

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
#include <iostream>
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
	int numBytes = 4;
	int _capacity = 0;
	int _inventorySize = 0;

	for (int j = numBytes - 1; j >= 0; --j){
		_capacity = (_capacity << 8) + buffer[i + j];
	}
	i += numBytes * 8;
	capacity = _capacity;

	for (int j = numBytes - 1; j >= 0; --j){
		_inventorySize = (_inventorySize << 8) + buffer[i + j];
	}
	i += numBytes * 8;
	
	int uid = 0;
	for (int k = 0; k < _inventorySize; ++k){
		uid = 0;
		for (int j = numBytes - 1; j >= 0; --j){
			uid = (uid << 8) + buffer[i + j];
		}
		i += numBytes * 8;
		inventoryMirror.push_back(uid);
	}
	return i;
}


Weapon::Weapon(DamageTypes _damageType, int _sidedDie):
damageType(_damageType), sidedDie(_sidedDie)
{

}

Weapon::Weapon()
{
	sidedDie = 0;
}

Weapon::~Weapon()
{

}

void Weapon::serialise(std::vector<uint8_t> &byteVector)
{
	serialiseInt(byteVector, static_cast<int>(damageType));
	serialiseInt(byteVector, sidedDie);
}

int Weapon::deserialise(char* buffer, int i)
{
	int numBytes = 4;
	int _damageType = 0;
	int _sidedDie = 0;


	for (int j = numBytes - 1; j >= 0; --j){
		_damageType = (_damageType << 8) + buffer[i + j];
	}
	damageType = static_cast<DamageTypes>(_damageType);
	i += numBytes * 8;

	
	for (int j = numBytes - 1; j >= 0; --j){
		_sidedDie = (_sidedDie << 8) + buffer[i + j];
	}
	sidedDie = _sidedDie;
	i += numBytes * 8;

	return i;
}

Armour::Armour(DamageTypes _resistance, DamageTypes _weakness):
resistance(_resistance), weakness(_weakness)
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
}

int Armour::deserialise(char* buffer, int i)
{
	int numBytes = 4;
	int _resistance = 0;
	int _weakness = 0;

	for (int j = numBytes - 1; j >= 0; --j){
		_resistance = (_resistance << 8) + buffer[i + j];
	}
	resistance = static_cast<DamageTypes>(_resistance);
	i += numBytes * 8;

	for (int j = numBytes - 1; j >= 0; --j){
		_weakness = (_weakness << 8) + buffer[i + j];
	}
	weakness = static_cast<DamageTypes>(_weakness);
	i += numBytes * 8;

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
	int numBytes = 4;
	int _slot = 0;

	for (int j = numBytes - 1; j >= 0; --j){
		_slot = (_slot << 8) + buffer[i + j];
	}
	slot = static_cast<EquipSlots>(_slot);
	i += numBytes * 8;

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
	int numBytes = 4;
	
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

	
	for (int j = numBytes - 1; j >= 0; --j){
		headKey = (headKey << 8) + buffer[i + j];
	}
	i += numBytes * 8;

	for (int j = numBytes - 1; j >= 0; --j){
		headValue = (headValue << 8) + buffer[i + j];
	}
	i += numBytes * 8;

	for (int j = numBytes - 1; j >= 0; --j){
		leftKey = (leftKey << 8) + buffer[i + j];
	}
	i += numBytes * 8;

	for (int j = numBytes - 1; j >= 0; --j){
		leftValue = (leftValue << 8) + buffer[i + j];
	}
	i += numBytes * 8;

	for (int j = numBytes - 1; j >= 0; --j){
		rightKey = (rightKey << 8) + buffer[i + j];
	}
	i += numBytes * 8;

	for (int j = numBytes - 1; j >= 0; --j){
		rightValue = (rightValue << 8) + buffer[i + j];
	}
	i += numBytes * 8;

	for (int j = numBytes - 1; j >= 0; --j){
		bodyKey = (bodyKey << 8) + buffer[i + j];
	}
	i += numBytes * 8;

	for (int j = numBytes - 1; j >= 0; --j){
		bodyValue = (bodyValue << 8) + buffer[i + j];
	}
	i += numBytes * 8;

	for (int j = numBytes - 1; j >= 0; --j){
		neckKey = (neckKey << 8) + buffer[i + j];
	}
	i += numBytes * 8;

	for (int j = numBytes - 1; j >= 0; --j){
		neckValue = (neckValue << 8) + buffer[i + j];
	}
	i += numBytes * 8;

	for (int j = numBytes - 1; j >= 0; --j){
		backKey = (backKey << 8) + buffer[i + j];
	}
	i += numBytes * 8;

	for (int j = numBytes - 1; j >= 0; --j){
		backValue = (backValue << 8) + buffer[i + j];
	}
	i += numBytes * 8;

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
	int numBytes = 4;
	int _func = 0;
	int _numUses = 0;

	for (int j = numBytes - 1; j >= 0; --j){
		_func = (_func << 8) + buffer[i + j];
	}
	i += numBytes * 8;
	funcToDo = static_cast<UseableFunctionEnums>(_func);
	
	for (int j = numBytes - 1; j >= 0; --j){
		_numUses = (_numUses << 8) + buffer[i + j];
	}
	i += numBytes * 8;
	numUses = _numUses;

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
	int numBytes = 4;
	int _roll = 0;
	
	for (int j = numBytes - 1; j >= 0; --j){
		_roll = (_roll << 8) + buffer[i + j];
	}
	i += numBytes * 8;
	roll = _roll;

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
	int numBytes = 4;
	
	int _radius = 0;
	int _roll = 0;
	int _type = 0;
	int _chance = 0;

	for (int j = numBytes - 1; j >= 0; --j){
		_radius = (_radius << 8) + buffer[i + j];
	}
	i += numBytes * 8;
	radius = _radius;

	for (int j = numBytes - 1; j >= 0; --j){
		_roll = (_roll << 8) + buffer[i + j];
	}
	i += numBytes * 8;
	roll = _roll;

	for (int j = numBytes - 1; j >= 0; --j){
		_roll = (_roll << 8) + buffer[i + j];
	}
	i += numBytes * 8;
	type = static_cast<DamageTypes>(_type);

	for (int j = numBytes - 1; j >= 0; --j){
		_chance = (_chance << 8) + buffer[i + j];
	}
	i += numBytes * 8;
	chance = _chance;

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
	int numBytes = 4;
	
	int _radius = 0;
	int _roll = 0;
	int _splashRadius = 0;
	int _type = 0;
	int _chance = 0;

	for (int j = numBytes - 1; j >= 0; --j){
		_radius = (_radius << 8) + buffer[i + j];
	}
	i += numBytes * 8;
	radius = _radius;

	for (int j = numBytes - 1; j >= 0; --j){
		_roll = (_roll << 8) + buffer[i + j];
	}
	i += numBytes * 8;
	roll = _roll;

	for (int j = numBytes - 1; j >= 0; --j){
		_splashRadius = (_splashRadius << 8) + buffer[i + j];
	}
	i += numBytes * 8;
	splashRadius = _splashRadius;

	for (int j = numBytes - 1; j >= 0; --j){
		_type = (_type << 8) + buffer[i + j];
	}
	i += numBytes * 8;
	type = static_cast<DamageTypes>(_type);

	for (int j = numBytes - 1; j >= 0; --j){
		_chance = (_chance << 8) + buffer[i + j];
	}
	i += numBytes * 8;
	chance = _chance;

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
	int numBytes = 4;
	
	int _radius = 0;
	int _status = 0;
	int _splashRadius = 0;

	for (int j = numBytes - 1; j >= 0; --j){
		_radius = (_radius << 8) + buffer[i + j];
	}
	i += numBytes * 8;
	radius = _radius;

	for (int j = numBytes - 1; j >= 0; --j){
		_status = (_status << 8) + buffer[i + j];
	}
	i += numBytes * 8;
	statusType = static_cast<StatusTypes>(_status);

	for (int j = numBytes - 1; j >= 0; --j){
		_splashRadius = (_splashRadius << 8) + buffer[i + j];
	}
	i += numBytes * 8;
	splashRadius = _splashRadius;

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

