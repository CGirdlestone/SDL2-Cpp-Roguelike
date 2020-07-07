
#include "GameObject.h"
#include <string>
#include <vector>

GameObject::GameObject(std::string name):
m_name(name)
{
  position = nullptr;
  renderable = nullptr;
  fighter = nullptr;
  actor = nullptr;
  player = nullptr;
  ai = nullptr;
  item = nullptr;
  container = nullptr;
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

  if(container != nullptr){
    delete container;
    container = nullptr;
  }
}
