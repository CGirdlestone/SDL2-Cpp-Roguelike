
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

