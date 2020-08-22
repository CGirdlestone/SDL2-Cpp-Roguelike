#ifndef COMPONENTS_H
#define COMPONENTS_H

#include "SDL2/SDL.h"
#include <vector>
#include <string>
#include <map>

#include "DamageTypes.h"
#include "Slots.h"
#include "UseableFunctionEnum.h"
#include "StatusTypes.h"
#include "GameObject.h"

void serialiseInt(std::vector<uint8_t> &byteVector, int x);
void serialiseString(std::vector<uint8_t> &byteVector, std::string stringToSerialise);

struct Position
{
  int x;
  int y;
  Position(int i, int j);
	Position();
  ~Position();
	void serialise(std::vector<uint8_t> &byteVector);
	int deserialise(char* buffer, int i);
};

struct Renderable
{
  char chr;
  SDL_Color colour;
	int spriteX;
	int spriteY;
	int sheet;
  Renderable(char _chr, SDL_Color _colour, int _spriteX, int _spriteY, int _sheet);
	Renderable();
  ~Renderable();
	void serialise(std::vector<uint8_t> &byteVector);
	int deserialise(char* buffer, int i);
};

struct Fighter
{
  int maxHealth;
  int health;
  int power;
  int defence;
  bool isAlive;
  Fighter(int _maxHealth, int _power, int _defence);
	Fighter();
  ~Fighter();
	void serialise(std::vector<uint8_t> &byteVector);
	int deserialise(char* buffer, int i);
};

struct Actor
{
	Actor();
  ~Actor();
	void serialise(std::vector<uint8_t> &byteVector);
	int deserialise(char* buffer, int i);
};

struct Player
{
	Player();
  ~Player();
	int level;
	int exp;
	int next;
	void serialise(std::vector<uint8_t> &byteVector);
	int deserialise(char* buffer, int i);
};

struct AI
{
	AI(int _exp, int _level);
	AI();
  ~AI();
	int exp;
	int level;
  std::vector<int> path;
	void serialise(std::vector<uint8_t> &byteVector);
	int deserialise(char* buffer, int i);
};

struct Item
{
  std::string description;
	int level;
  Item(std::string desc, int _level);
	Item();
  ~Item();
	void serialise(std::vector<uint8_t> &byteVector);
	int deserialise(char* buffer, int i);
};

struct Inventory
{
  int capacity;
  std::vector<GameObject*> inventory;
	std::vector<int> inventoryMirror;
  Inventory(int _capacity);
	Inventory();
  ~Inventory();
	void serialise(std::vector<uint8_t> &byteVector);
	int deserialise(char* buffer, int i);
};

struct Weapon
{
  DamageTypes damageType;
  int sidedDie;
	bool twoHanded;
  Weapon(DamageTypes _damageType, int _sidedDie, bool _twoHanded);
	Weapon();
  ~Weapon();
	void serialise(std::vector<uint8_t> &byteVector);
	int deserialise(char* buffer, int i);
};

struct Armour
{
  DamageTypes resistance;
  DamageTypes weakness;
	int armourBonus;
  Armour(DamageTypes _resistance, DamageTypes _weakness, int _armourBonus);
	Armour();
  ~Armour();
	void serialise(std::vector<uint8_t> &byteVector);
	int deserialise(char* buffer, int i);
};

struct Wearable
{
  Wearable(EquipSlots _slot);
	Wearable();
	~Wearable();
	EquipSlots slot;
	void serialise(std::vector<uint8_t> &byteVector);
	int deserialise(char* buffer, int i);
};

struct Body
{
  std::map<EquipSlots, GameObject*> slots;
	std::map<int, int> slotsMirror;
  Body();
  ~Body();
	void serialise(std::vector<uint8_t> &byteVector);
	int deserialise(char* buffer, int i);
};

struct Useable
{
	Useable(UseableFunctionEnums func, int _numUses);
	Useable();
	~Useable();	
	UseableFunctionEnums funcToDo;
	int numUses;
	void serialise(std::vector<uint8_t> &byteVector);
	int deserialise(char* buffer, int i);
};

struct Healing
{
	Healing(int _roll);
	Healing();
	~Healing();
	int roll;
	void serialise(std::vector<uint8_t> &byteVector);
	int deserialise(char* buffer, int i);
};

struct Damage
{
	Damage(int _radius, int _roll, DamageTypes _type, int _chance);
	Damage();
	~Damage();
	int radius;
	int roll;
	DamageTypes type;
	int chance;
	void serialise(std::vector<uint8_t> &byteVector);
	int deserialise(char* buffer, int i);
};

struct AreaDamage
{
	AreaDamage(int _radius, int _roll, int _splashRadius, DamageTypes _type, int _chance);
	AreaDamage();
	~AreaDamage();
	int radius;
	int roll;
	int splashRadius;
	DamageTypes type;
	int chance;
	void serialise(std::vector<uint8_t> &byteVector);
	int deserialise(char* buffer, int i);
};

struct Status
{
	Status(int _radius, StatusTypes _status, int _splashRadius);
	Status();
	~Status();
	int radius;
	StatusTypes statusType;
	int splashRadius;
	void serialise(std::vector<uint8_t> &byteVector);
	int deserialise(char* buffer, int i);
};

struct Consumable
{
	Consumable();
	~Consumable();
	void serialise(std::vector<uint8_t> &byteVector);
	int deserialise(char* buffer, int i);
};

struct Stairs
{
	Stairs();
	~Stairs();
	void serialise(std::vector<uint8_t> &byteVector);
	int deserialise(char* buffer, int i);
};

struct StatusContainer
{
	StatusContainer();
	~StatusContainer();
	void serialise(std::vector<uint8_t> &byteVector);
	int deserialise(char* buffer, int i);
	std::map<StatusTypes, std::pair<int, int>> statuses;
};

#endif
