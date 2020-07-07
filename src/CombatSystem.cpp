#include <iostream>
#include <vector>

#include "CombatSystem.h"
#include "EventManager.h"
#include "Events.h"
#include "EventTypes.h"

CombatSystem::CombatSystem(EventManager* eventManager, std::vector<GameObject*> *entities):
m_eventManager(eventManager), m_entities(entities)
{
  m_eventManager->registerSystem(ATTACK, this);
  m_eventManager->registerSystem(ONHIT, this);
  m_eventManager->registerSystem(DAMAGE, this);
  m_eventManager->registerSystem(DEAD, this);
}

CombatSystem::~CombatSystem()
{
  m_eventManager = nullptr;
  m_entities = nullptr;
}

void CombatSystem::notify(AttackEvent event)
{
  // to do
}

void CombatSystem::notify(OnHitEvent event)
{
  // to do
}

void CombatSystem::notify(DamageEvent event)
{
  // to do
}

void CombatSystem::notify(DeadEvent event)
{
  // to do
}
