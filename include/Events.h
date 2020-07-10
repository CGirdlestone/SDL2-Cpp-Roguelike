
#ifndef EVENTS_H
#define EVENTS_H

#include <string>
#include "EventTypes.h"
#include "SceneTypes.h"

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

struct TakeEvent : Event
{
  TakeEvent(int uid, int x, int y);
  virtual ~TakeEvent();
  int m_uid;
  int m_x;
  int m_y;
};

struct OnPickUpEvent : Event
{
  OnPickUpEvent(int uid, std::string name);
  virtual ~OnPickUpEvent();
  int m_uid;
  std::string m_name;
};

struct PushScene : Event
{
  PushScene(SceneTypes scene);
  virtual ~PushScene();
  SceneTypes m_scene;
};

struct PopScene : Event
{
  PopScene(int numPops);
  virtual ~PopScene();
  int m_numPops;
};

struct QuitEvent : Event
{
  QuitEvent();
  virtual ~QuitEvent();
};


#endif
