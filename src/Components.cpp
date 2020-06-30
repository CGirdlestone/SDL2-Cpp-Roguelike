
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

Fighter::Fighter(int maxHealth, int power, int defence, bool isAlive)
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

AI::~AI()
{

}

Item::~Item()
{

}

Container::Container(int capacity)
{
  capacity = capacity;
}

Container::~Container()
{

}

bool Container::addItem(GameObject *item)
{
  //inventory.push_back(item);
  return true;
}

bool Container::removeItem(GameObject *item)
{
  return true;
}
