
#include <vector>
#include <map>
#include <string>
#include "SDL2/SDL.h"

#include "MessageLog.h"
#include "Message.h"
#include "GameObject.h"




MessageLog::MessageLog(int x_buffer, int y_buffer, EventManager* eventManager, std::map<int, GameObject*> *entities)
{
    m_x_buffer = x_buffer;
    m_y_buffer = y_buffer;
    m_eventManager = eventManager;
    m_entities = entities;
    m_eventManager->registerSystem(ONHIT, this);
    m_eventManager->registerSystem(CRITICALHIT, this);
    m_eventManager->registerSystem(ONMISS, this);
    m_eventManager->registerSystem(DAMAGE, this);
    m_eventManager->registerSystem(DEAD, this);
    m_eventManager->registerSystem(ONPICKUP, this);
		m_eventManager->registerSystem(DROP, this);
		m_eventManager->registerSystem(MESSAGE, this);
}

MessageLog::~MessageLog()
{

}

void MessageLog::addMessage(std::string msg, SDL_Color colour)
{
    //
    Message _msg = Message(msg, colour);

    m_messageQueue.push_back(_msg);

    if(static_cast<int>(m_messageQueue.size()) >= m_y_buffer){
       m_messageQueue.erase(m_messageQueue.begin());
    }
}

void MessageLog::addMessage(std::string msg)
{
    SDL_Color colour = {0xFF, 0xFF, 0xFF};

    Message _msg = Message(msg, colour);

    m_messageQueue.push_back(_msg);

    if(!(static_cast<int>(m_messageQueue.size()) <= m_y_buffer)){
       m_messageQueue.erase(m_messageQueue.begin());
    }
}

void MessageLog::ageMessages(Uint32 ticks)
{
    std::vector<Message> aliveMessages;

    if(static_cast<int>(m_messageQueue.size()) > 0){
        for(Message msg : m_messageQueue){
            if (msg.m_lifetime < ticks){
                msg.m_lifetime = 0;
            } else {
                msg.m_lifetime -= ticks;
            }

            if (msg.m_lifetime > 0){
                aliveMessages.push_back(msg);
            }
        }
    }

    m_messageQueue = aliveMessages;
}

std::vector<Message> MessageLog::getMessages()
{
    return m_messageQueue;
}

void MessageLog::notify(AttackEvent event)
{
  // to do
}

void MessageLog::notify(OnHitEvent event)
{
  std::string attackerName = m_entities->at(event.m_attacker_uid)->m_name;
  std::string defenderName = m_entities->at(event.m_defender_uid)->m_name;
  std::string msg = attackerName + " hits " + defenderName;
  addMessage(msg);
}


void MessageLog::notify(OnCriticalHitEvent event)
{
  std::string attackerName = m_entities->at(event.m_attacker_uid)->m_name;
  std::string defenderName = m_entities->at(event.m_defender_uid)->m_name;
  std::string msg = attackerName + " hits " + defenderName + " - CRITICAL HIT";
  addMessage(msg);
}

void MessageLog::notify(OnMissEvent event)
{
  std::string attackerName = m_entities->at(event.m_attacker_uid)->m_name;
  std::string defenderName = m_entities->at(event.m_defender_uid)->m_name;
  std::string msg = attackerName + " misses " + defenderName;
  addMessage(msg);
}


void MessageLog::notify(DamageEvent event)
{
	std::string msg;  
	std::string defenderName = m_entities->at(event.m_uid)->m_name;
  
	int dmg = event.m_damage;
	
 	if (dmg >= 0){
		msg = defenderName + " suffers " + std::to_string(dmg) + " points of damage!";
  } else {
		msg = defenderName + " heals for " + std::to_string(-1 * dmg) + " health points!";
	}
	addMessage(msg);
}

void MessageLog::notify(DeadEvent event)
{
  std::string defenderName = m_entities->at(event.m_uid)->m_name;
  std::string msg = defenderName + " has been slain!";
  addMessage(msg);

	std::string expGain = "+" + std::to_string(m_entities->at(event.m_uid)->ai->exp) + " xp";
	SDL_Color colour = {0xef, 0xac, 0x28};
	addMessage(expGain, colour);
}

void MessageLog::notify(OnPickUpEvent event)
{
  std::string name = m_entities->at(event.m_uid)->m_name;
  std::string msg = name + " has picked up " + event.m_name;
  addMessage(msg);
}

void MessageLog::notify(DropEvent event)
{
	std::string name = m_entities->at(event.m_item_uid)->m_name;
	std::string msg = name + " dropped!";
	addMessage(msg);
}

void MessageLog::notify(MessageEvent event)
{
	addMessage(event.m_msg);
}
