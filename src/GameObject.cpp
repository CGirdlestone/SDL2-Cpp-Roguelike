
#include "GameObject.h"
#include <string>
#include <vector>

GameObject::GameObject(std::string name, int uid):
m_name(name), m_uid(uid)
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
}
