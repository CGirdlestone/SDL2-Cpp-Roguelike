

#include "EventTypes.h"
#include "Events.h"
#include "GameObject.h"

Event::~Event()
{

}


MoveEvent::MoveEvent(int dx, int dy, int uid):
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

OnCriticalHitEvent::OnCriticalHitEvent(int attacker_uid, int defender_uid):
m_attacker_uid(attacker_uid), m_defender_uid(defender_uid)
{
  m_type = CRITICALHIT;
}

OnCriticalHitEvent::~OnCriticalHitEvent()
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

TakeEvent::TakeEvent(int uid, int x, int y):
m_uid(uid), m_x(x), m_y(y)
{
  m_type = TAKE;
}

TakeEvent::~TakeEvent()
{

}

OnPickUpEvent::OnPickUpEvent(int uid, std::string name):
m_uid(uid), m_name(name)
{
  m_type = ONPICKUP;
}

OnPickUpEvent::~OnPickUpEvent()
{

}

PushScene::PushScene(SceneTypes scene):
m_scene(scene)
{
  m_type = PUSHSCENE;
}

PushScene::~PushScene()
{

}

PopScene::PopScene(int numPops):
m_numPops(numPops)
{
  m_type = POPSCENE;
}

PopScene::~PopScene()
{

}

QuitEvent::QuitEvent()
{
  m_type = QUIT;
}

QuitEvent::~QuitEvent()
{

}

DropEvent::DropEvent(int actor_uid, int item_uid, int x, int y):
m_actor_uid(actor_uid), m_item_uid(item_uid), m_x(x), m_y(y)
{
	m_type = DROP;
}

DropEvent::~DropEvent()
{

}

EquipEvent::EquipEvent(int actor_uid, int item_uid):
m_actor_uid(actor_uid), m_item_uid(item_uid)
{
	m_type = EQUIP;
}

EquipEvent::~EquipEvent()
{

}

UnequipEvent::UnequipEvent(int actor_uid, int item_uid, int slotNum):
m_actor_uid(actor_uid), m_item_uid(item_uid), m_slotNum(slotNum)
{
	m_type = UNEQUIP;
}

UnequipEvent::~UnequipEvent()
{

}

UseItemEvent::UseItemEvent(int user_uid, int item_uid, int target_uid):
m_user_uid(user_uid), m_item_uid(item_uid), m_target_uid(target_uid)
{
	m_type = USEITEM;
}

UseItemEvent::~UseItemEvent()
{

}

PassUserInfoEvent::PassUserInfoEvent(int user_uid, int item_uid):
m_user_uid(user_uid), m_item_uid(item_uid)
{
	m_type = PASSUSERINFO;
}

PassUserInfoEvent::~PassUserInfoEvent()
{

}

MessageEvent::MessageEvent(std::string msg):
m_msg(msg)
{
	m_type = MESSAGE;
}

MessageEvent::~MessageEvent()
{

}

PlayerTurnOverEvent::PlayerTurnOverEvent()
{
	m_type = PLAYERTURNOVER;
}

PlayerTurnOverEvent::~PlayerTurnOverEvent()
{

}

LoadEvent::LoadEvent()
{
	m_type = LOADGAME;
}

LoadEvent::~LoadEvent()
{

}
