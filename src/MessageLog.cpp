
#include <vector>
#include <string>
#include "SDL2/SDL.h"

#include "MessageLog.h"
#include "Message.h"
#include "GameObject.h"




MessageLog::MessageLog(int x_buffer, int y_buffer, EventManager* eventManager, std::vector<GameObject*> *entities)
{
    m_x_buffer = x_buffer;
    m_y_buffer = y_buffer;
    m_eventManager = eventManager;
    m_entities = entities;
    m_eventManager->registerSystem(ONHIT, this);
    m_eventManager->registerSystem(ONMISS, this);
    m_eventManager->registerSystem(DAMAGE, this);
    m_eventManager->registerSystem(DEAD, this);
    m_eventManager->registerSystem(ONPICKUP, this);
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

// void MessageLog::notify(MoveEvent event)
// {
//   // to do
//   addMessage(m_entities->at(event.m_uid)->m_name);
// }

void MessageLog::notify(AttackEvent event)
{
  // to do
}

void MessageLog::notify(OnHitEvent event)
{
  // to do
  std::string attackerName = m_entities->at(event.m_attacker_uid)->m_name;
  std::string defenderName = m_entities->at(event.m_defender_uid)->m_name;
  std::string msg = attackerName + " hits " + defenderName;
  addMessage(msg);
}


void MessageLog::notify(OnMissEvent event)
{
  // to do
  std::string attackerName = m_entities->at(event.m_attacker_uid)->m_name;
  std::string defenderName = m_entities->at(event.m_defender_uid)->m_name;
  std::string msg = attackerName + " misses " + defenderName;
  addMessage(msg);
}


void MessageLog::notify(DamageEvent event)
{
  // to do
  std::string defenderName = m_entities->at(event.m_uid)->m_name;
  int dmg = event.m_damage;
  std::string msg = defenderName + " suffers " + std::to_string(dmg) + " points of damage!";
  addMessage(msg);
}

void MessageLog::notify(DeadEvent event)
{
  // to do
  std::string defenderName = m_entities->at(event.m_uid)->m_name;
  std::string msg = defenderName + " has been slain!";
  addMessage(msg);
}

void MessageLog::notify(OnPickUpEvent event)
{
  // to do

  std::string name = m_entities->at(event.m_uid)->m_name;
  std::string msg = name + " has picked up " + event.m_name;
  addMessage(msg);
}
