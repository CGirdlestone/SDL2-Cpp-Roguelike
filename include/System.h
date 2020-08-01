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
	virtual void notify(OnCriticalHitEvent event) {};
  virtual void notify(OnMissEvent event) {};
  virtual void notify(DamageEvent event) {};
  virtual void notify(DeadEvent event) {};
  virtual void notify(TakeEvent event) {};
  virtual void notify(OnPickUpEvent event) {};
  virtual void notify(PushScene event) {};
  virtual void notify(PopScene event) {};
  virtual void notify(QuitEvent event) {};
	virtual void notify(DropEvent event) {};
	virtual void notify(EquipEvent event) {};
	virtual void notify(UnequipEvent event) {};
	virtual void notify(UseItemEvent event) {};
	virtual void notify(PassUserInfoEvent event) {};
	virtual void notify(MessageEvent event) {};
	virtual void notify(PlayerTurnOverEvent event) {};
	virtual void notify(LoadEvent event) {};
	virtual void notify(RestartEvent event) {};
};

#endif
