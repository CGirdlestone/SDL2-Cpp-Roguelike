
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

	template<typename T>
	void pushEvent(const T& event){
		for (unsigned int i = 0; i < m_subscribers.at(event.m_type).size(); ++i){
			m_subscribers.at(event.m_type).at(i)->notify(event);
		}
	}

private:
  std::map<EventTypes, std::vector<System*>> m_subscribers;
};

#endif
