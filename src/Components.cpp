
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

Player::~Player()
{

}

Item::Item(std::string desc):
description(desc)
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

Weapon::Weapon(DamageTypes _damageType, EquipSlots _slot, int _sidedDie):
damageType(_damageType), slot(_slot), sidedDie(_sidedDie)
{

}

Weapon::~Weapon()
{

}


Armour::Armour(DamageTypes _resistance, DamageTypes _weakness, EquipSlots _slot):
resistance(_resistance), weakness(_weakness), slot(_slot)
{

}

Armour::~Armour()
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
