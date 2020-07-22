
#include "SDL2/SDL.h"

#include "Components.h"
#include <string>

Position::Position(int i, int j)
{
  x = i;
  y = j;
}
Position::~Position()
{

}


Renderable::Renderable(char _chr, SDL_Color _colour)
{
    chr = _chr;
    colour = _colour;
}

Renderable::~Renderable()
{

}

Fighter::Fighter(int _maxHealth, int _power, int _defence):
maxHealth(_maxHealth), health(_maxHealth), power(_power), defence(_defence), isAlive(true)
{

}

Fighter::~Fighter()
{

}

Actor::~Actor()
{

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

Item::Item(std::string desc):
description(desc)
{

}

AI::AI(int _exp):
exp(_exp)
{

}

AI::~AI()
{

}

Item::~Item()
{

}

Inventory::Inventory(int _capacity):
capacity(_capacity)
{

}

Inventory::~Inventory()
{

}

Weapon::Weapon(DamageTypes _damageType, int _sidedDie):
damageType(_damageType), sidedDie(_sidedDie)
{

}

Weapon::~Weapon()
{

}


Armour::Armour(DamageTypes _resistance, DamageTypes _weakness):
resistance(_resistance), weakness(_weakness)
{

}

Armour::~Armour()
{

}

Wearable::Wearable(EquipSlots _slot):
slot(_slot)
{

}

Wearable::~Wearable()
{

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

Useable::Useable(UseableFunctionEnums func, int _numUses):
funcToDo(func), numUses(_numUses)
{

}

Useable::~Useable()
{

}

Healing::Healing(int _roll):
roll(_roll)
{

}

Healing::~Healing()
{

}

Damage::Damage(int _radius, int _roll, DamageTypes _type, int _chance):
radius(_radius), roll(_roll), type(_type), chance(_chance)
{

}

Damage::~Damage()
{

}

AreaDamage::AreaDamage(int _radius, int _roll, int _splashRadius, DamageTypes _type, int _chance):
radius(_radius), roll(_roll), splashRadius(_splashRadius), type(_type), chance(_chance)
{

}

AreaDamage::~AreaDamage()
{

}

Status::Status(int _radius, StatusTypes _status, int _splashRadius):
radius(_radius), statusType(_status), splashRadius(_splashRadius)
{

}

Status::~Status()
{

}

Consumable::Consumable()
{

}

Consumable::~Consumable()
{

}

Stairs::Stairs()
{

}

Stairs::~Stairs()
{

}
