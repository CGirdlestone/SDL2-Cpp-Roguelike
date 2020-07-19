
#include <iostream>
#include "EventManager.h"
#include "Events.h"
#include "System.h"


EventManager::EventManager()
{
  //
}

EventManager::~EventManager()
{
  //
}

void EventManager::registerSystem(EventTypes eventType, System* s)
{
  if (m_subscribers.find(eventType) == m_subscribers.end()){
    std::vector<System*> subscribers;
    subscribers.push_back(s);
    m_subscribers.insert({eventType, subscribers});
  } else {
    m_subscribers.at(eventType).push_back(s);
  }
}

void EventManager::pushEvent(MoveEvent event)
{
  for (int i = 0; i < static_cast<int>(m_subscribers.at(event.m_type).size()); ++i)
  {
    m_subscribers.at(event.m_type).at(i)->notify(event);
  }
}

void EventManager::pushEvent(AttackEvent event)
{
  for (int i = 0; i < static_cast<int>(m_subscribers.at(event.m_type).size()); ++i)
  {
    m_subscribers.at(event.m_type).at(i)->notify(event);
  }
}

void EventManager::pushEvent(OnHitEvent event)
{
  for (int i = 0; i < static_cast<int>(m_subscribers.at(event.m_type).size()); ++i)
  {
    m_subscribers.at(event.m_type).at(i)->notify(event);
  }
}

void EventManager::pushEvent(OnMissEvent event)
{
  for (int i = 0; i < static_cast<int>(m_subscribers.at(event.m_type).size()); ++i)
  {
    m_subscribers.at(event.m_type).at(i)->notify(event);
  }
}

void EventManager::pushEvent(DamageEvent event)
{
  for (int i = 0; i < static_cast<int>(m_subscribers.at(event.m_type).size()); ++i)
  {
    m_subscribers.at(event.m_type).at(i)->notify(event);
  }
}

void EventManager::pushEvent(DeadEvent event)
{
  for (int i = 0; i < static_cast<int>(m_subscribers.at(event.m_type).size()); ++i)
  {
    m_subscribers.at(event.m_type).at(i)->notify(event);
  }
}

void EventManager::pushEvent(TakeEvent event)
{
  for (int i = 0; i < static_cast<int>(m_subscribers.at(event.m_type).size()); ++i)
  {
    m_subscribers.at(event.m_type).at(i)->notify(event);
  }
}

void EventManager::pushEvent(OnPickUpEvent event)
{
  for (int i = 0; i < static_cast<int>(m_subscribers.at(event.m_type).size()); ++i)
  {
    m_subscribers.at(event.m_type).at(i)->notify(event);
  }
}

void EventManager::pushEvent(PushScene event)
{
  for (int i = 0; i < static_cast<int>(m_subscribers.at(event.m_type).size()); ++i)
  {
    m_subscribers.at(event.m_type).at(i)->notify(event);
  }
}

void EventManager::pushEvent(PopScene event)
{
  for (int i = 0; i < static_cast<int>(m_subscribers.at(event.m_type).size()); ++i)
  {
    m_subscribers.at(event.m_type).at(i)->notify(event);
  }
}

void EventManager::pushEvent(QuitEvent event)
{
  for (int i = 0; i < static_cast<int>(m_subscribers.at(event.m_type).size()); ++i)
  {
    m_subscribers.at(event.m_type).at(i)->notify(event);
  }
}

void EventManager::pushEvent(DropEvent event)
{
	for (int i = 0; i < static_cast<int>(m_subscribers.at(event.m_type).size()); ++i)
	{
		m_subscribers.at(event.m_type).at(i)->notify(event);
	}
}

void EventManager::pushEvent(EquipEvent event)
{
	for (int i = 0; i < static_cast<int>(m_subscribers.at(event.m_type).size()); ++i)
	{
		m_subscribers.at(event.m_type).at(i)->notify(event);
	}
}

void EventManager::pushEvent(UnequipEvent event)
{
	for (int i = 0; i < static_cast<int>(m_subscribers.at(event.m_type).size()); ++i)
	{
		m_subscribers.at(event.m_type).at(i)->notify(event);
	}
}

void EventManager::pushEvent(UseItemEvent event)
{
	for (int i = 0; i < static_cast<int>(m_subscribers.at(event.m_type).size()); ++i)
	{
		m_subscribers.at(event.m_type).at(i)->notify(event);
	}
}
