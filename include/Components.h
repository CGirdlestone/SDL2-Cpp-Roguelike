#ifndef COMPONENTS_H
#define COMPONENTS_H

#include "SDL2/SDL.h"
#include <vector>

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
  ~Item();
};

struct Container
{
    std::vector<GameObject*> inventory;
    Container(int capacity);
    ~Container();
    bool addItem(GameObject *item);
    bool removeItem(GameObject *item);
};

#endif
