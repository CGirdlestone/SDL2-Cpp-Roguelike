#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <string>
#include <vector>

struct Position;
struct Renderable;
struct Fighter;
struct Actor;
struct Player;
struct AI;
struct Item;
struct Inventory;
struct Weapon;
struct Armour;
struct Wearable;
struct Body;
struct Useable;
struct Healing;
struct Damage;
struct AreaDamage;
struct Status;
struct Consumable;
struct Stairs;
struct StatusContainer;

class GameObject
{
public:
	GameObject();
  ~GameObject();

	void serialise(std::vector<uint8_t> &byteVector);
	int deserialise(char* buffer, int i);

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
	Stairs *stairs;
	StatusContainer *statusContainer;

protected:

private:
};

#endif
