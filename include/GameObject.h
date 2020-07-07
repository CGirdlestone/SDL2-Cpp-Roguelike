#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <string>

#include "Components.h"

class GameObject
{
public:
  GameObject(std::string name);
  ~GameObject();

  std::string m_name;
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
