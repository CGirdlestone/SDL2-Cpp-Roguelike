#ifndef SYSTEM_H
#define SYSTEM_H

#include "Events.h"

class EventManager;

class System
{
public:
  virtual ~System() {};
  virtual void notify(MoveEvent event) {};
  virtual void notify(AttackEvent event) {};
  virtual void notify(OnHitEvent event) {};
  virtual void notify(OnMissEvent event) {};
  virtual void notify(DamageEvent event) {};
  virtual void notify(DeadEvent event) {};
};

#endif