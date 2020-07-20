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

class GameObject;

struct Position
{
  int x;
  int y;
  Position(int i, int j);
  ~Position();
};

struct Renderable
{
  char chr;
  SDL_Color colour;
  Renderable(char _chr, SDL_Color _colour);
  ~Renderable();
};

struct Fighter
{
  int maxHealth;
  int health;
  int power;
  int defence;
  bool isAlive;
  Fighter(int _maxHealth, int _power, int _defence);
  ~Fighter();
};

struct Actor
{
  ~Actor();
};

struct Player
{
  ~Player();
};

struct AI
{
  std::vector<int> path;
  ~AI();
};

struct Item
{
  std::string description;
  Item(std::string desc);
  ~Item();
};

struct Inventory
{
    int capacity;
    std::vector<GameObject*> inventory;
    Inventory(int _capacity);
    ~Inventory();
};

struct Weapon
{
  DamageTypes damageType;
  int sidedDie;
  Weapon(DamageTypes _damageType, int _sidedDie);
  ~Weapon();
};

struct Armour
{
  DamageTypes resistance;
  DamageTypes weakness;
  Armour(DamageTypes _resistance, DamageTypes _weakness);
  ~Armour();
};

struct Wearable
{
  Wearable(EquipSlots _slot);
	~Wearable();
	EquipSlots slot;
};

struct Body
{
  std::map<EquipSlots, GameObject*> slots;
  Body();
  ~Body();
};

struct Useable
{
	Useable(UseableFunctionEnums func, int _numUses);
	~Useable();	
	UseableFunctionEnums funcToDo;
	int numUses;
};

struct Healing
{
	Healing(int _roll);
	~Healing();
	int roll;
};

struct Damage
{
	Damage(int _radius, int _roll, DamageTypes _type, int _chance);
	~Damage();
	int radius;
	int roll;
	DamageTypes type;
	int chance;
};

struct AreaDamage
{
	AreaDamage(int _radius, int _roll, int _splashRadius, DamageTypes _type, int _chance);
	~AreaDamage();
	int radius;
	int roll;
	int splashRadius;
	DamageTypes type;
	int chance;
};

struct Status
{
	Status(int _radius, StatusTypes _status, int _splashRadius);
	~Status();
	int radius;
	StatusTypes statusType;
	int splashRadius;
};

struct Consumable
{
	Consumable();
	~Consumable();
};


#endif
