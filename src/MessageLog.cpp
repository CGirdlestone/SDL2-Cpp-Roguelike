
#include <vector>
#include <string>
#include "SDL2/SDL.h"

#include "MessageLog.h"
#include "Message.h"




MessageLog::MessageLog(int x_buffer, int y_buffer)
{
    m_x_buffer = x_buffer;
    m_y_buffer = y_buffer;
}

MessageLog::~MessageLog()
{

}

void MessageLog::addMessage(std::string msg, SDL_Color colour)
{
    //
    Message _msg = Message(msg, colour);

    m_messageQueue.push_back(_msg);

    if(m_messageQueue.size() >= m_y_buffer){
       m_messageQueue.erase(m_messageQueue.begin());
    }
}

void MessageLog::addMessage(std::string msg)
{
    SDL_Color colour = {0xFF, 0xFF, 0xFF};

    Message _msg = Message(msg, colour);

    m_messageQueue.push_back(_msg);

    if(!(m_messageQueue.size() <= m_y_buffer)){
       m_messageQueue.erase(m_messageQueue.begin());
    }
}

void MessageLog::ageMessages(Uint32 ticks)
{
    std::vector<Message> aliveMessages;

    if(m_messageQueue.size() > 0){
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
