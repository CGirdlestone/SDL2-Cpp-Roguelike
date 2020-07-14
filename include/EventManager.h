
#ifndef EVENTMANAGER_H
#define EVENTMANAGER_H

#include <map>
#include <vector>
#include "EventTypes.h"
#include "Events.h"

class System;

class EventManager
{
public:
  EventManager();
  ~EventManager();
  void registerSystem(EventTypes eventType, System* s);
  void pushEvent(MoveEvent event);
  void pushEvent(AttackEvent event);
  void pushEvent(OnHitEvent event);
  void pushEvent(OnMissEvent event);
  void pushEvent(DamageEvent event);
  void pushEvent(DeadEvent event);
  void pushEvent(TakeEvent event);
  void pushEvent(OnPickUpEvent event);
  void pushEvent(PushScene event);
  void pushEvent(PopScene event);
  void pushEvent(QuitEvent event);
	void pushEvent(DropEvent event);
	void pushEvent(EquipEvent event);

private:
  std::map<EventTypes, std::vector<System*>> m_subscribers;
};

#endif
