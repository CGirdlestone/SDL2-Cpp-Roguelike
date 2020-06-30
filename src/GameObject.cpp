
#include "GameObject.h"
#include <vector>

GameObject::GameObject()
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
  if(position){
    delete position;
    position = nullptr;
  }

  if(renderable){
    delete renderable;
    renderable = nullptr;
  }

  if(fighter){
    delete fighter;
    fighter = nullptr;
  }

  if(actor){
    delete actor;
    actor = nullptr;
  }

  if(player){
    delete player;
    player = nullptr;
  }

  if(ai){
    delete ai;
    ai = nullptr;
  }

  if(item){
    delete item;
    item = nullptr;
  }

  if(container){
    delete container;
    container = nullptr;
  }
}
