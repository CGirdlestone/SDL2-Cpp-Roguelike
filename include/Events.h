
#ifndef EVENTS_H
#define EVENTS_H

#include "EventTypes.h"

struct Event
{
  virtual ~Event() = 0;
  EventTypes m_type;
};

struct MoveEvent : Event
{
  MoveEvent(int dx, int dy, int uid);
  virtual ~MoveEvent();
  int m_uid;
  int m_dx;
  int m_dy;
};

struct AttackEvent : Event
{
  AttackEvent(int attacker_uid, int defender_uid);
  virtual ~AttackEvent();
  int m_attacker_uid;
  int m_defender_uid;
};

struct OnHitEvent : Event
{
  OnHitEvent(int attacker_uid, int defender_uid);
  virtual ~OnHitEvent();
  int m_attacker_uid;
  int m_defender_uid;
};

struct OnMissEvent : Event
{
  OnMissEvent(int attacker_uid, int defender_uid);
  virtual ~OnMissEvent();
  int m_attacker_uid;
  int m_defender_uid;
};

struct DamageEvent : Event
{
  DamageEvent(int uid, int damage);
  virtual ~DamageEvent();
  int m_uid;
  int m_damage;
};

struct DeadEvent : Event
{
  DeadEvent(int uid);
  virtual ~DeadEvent();
  int m_uid;
};



#endif
