#ifndef COMPONENTS_H
#define COMPONENTS_H

#include "SDL2/SDL.h"
#include <vector>
#include <string>
#include <map>
#include "DamageTypes.h"
#include "Slots.h"

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
  EquipSlots slot;
  int sidedDie;
  Weapon(DamageTypes _damageType, EquipSlots _slot, int _sidedDie);
  ~Weapon();
};

struct Armour
{
  DamageTypes resistance;
  DamageTypes weakness;
  EquipSlots slot;
  Armour(DamageTypes _resistance, DamageTypes _weakness, EquipSlots _slot);
  ~Armour();
};

struct Wearable
{
  ~Wearable();
};

struct Body
{
  std::map<EquipSlots, GameObject*> slots;
  Body();
  ~Body();
};

#endif
