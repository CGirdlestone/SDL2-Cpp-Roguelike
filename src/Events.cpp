

#include "EventTypes.h"
#include "Events.h"

Event::~Event()
{

}


MoveEvent::MoveEvent(int uid, int dx, int dy):
m_uid(uid), m_dx(dx), m_dy(dy)
{
  m_type = MOVE;
}

MoveEvent::~MoveEvent()
{

}

AttackEvent::AttackEvent(int attacker_uid, int defender_uid):
m_attacker_uid(attacker_uid), m_defender_uid(defender_uid)
{
  m_type = ATTACK;
}

AttackEvent::~AttackEvent()
{

}

OnHitEvent::OnHitEvent(int attacker_uid, int defender_uid):
m_attacker_uid(attacker_uid), m_defender_uid(defender_uid)
{
  m_type = ONHIT;
}

OnHitEvent::~OnHitEvent()
{

}

OnMissEvent::OnMissEvent(int attacker_uid, int defender_uid):
m_attacker_uid(attacker_uid), m_defender_uid(defender_uid)
{
  m_type = ONMISS;
}

OnMissEvent::~OnMissEvent()
{

}

DamageEvent::DamageEvent(int uid, int damage):
m_uid(uid), m_damage(damage)
{
  m_type = DAMAGE;
}

DamageEvent::~DamageEvent()
{

}

DeadEvent::DeadEvent(int uid):
m_uid(uid)
{
 m_type = DEAD;
}

DeadEvent::~DeadEvent()
{

}
