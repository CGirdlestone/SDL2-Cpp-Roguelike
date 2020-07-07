
#ifndef COMBATSYSTEM_H
#define COMBATSYSTEM_H

#include <vector>
#include "System.h"
#include "Events.h"
#include "GameObject.h"

class EventManager;

class CombatSystem : public System
{
public:
  CombatSystem(EventManager* eventManager, std::vector<GameObject*> *entities);
  virtual ~CombatSystem();

  virtual void notify(AttackEvent event);
  virtual void notify(OnHitEvent event);
  virtual void notify(DamageEvent event);
  virtual void notify(DeadEvent event);
private:
  EventManager* m_eventManager;
  std::vector<GameObject*> *m_entities;
};


#endif
