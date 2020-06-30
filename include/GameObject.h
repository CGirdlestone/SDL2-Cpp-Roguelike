#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Components.h"

class GameObject
{
public:
  GameObject();
  ~GameObject();

  Position *position;
  Renderable *renderable;
  Fighter *fighter;
  Actor *actor;
  Player *player;
  AI *ai;
  Item *item;
  Container *container;
protected:

private:
};

#endif
