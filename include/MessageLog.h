#ifndef MESSAGELOG_H
#define MESSAGELOG_H

#include <vector>
#include <string>
#include "SDL2/SDL.h"

#include "Message.h"

class MessageLog
{
public:
    MessageLog(int x_buffer, int y_buffer);
    ~MessageLog();
    void addMessage(std::string msg, SDL_Color colour);
    void addMessage(std::string msg);
    std::vector<Message> getMessages();
    int getm_y_buffer(){return m_y_buffer;};
protected:

private:
    std::vector<Message> m_messageQueue;
    int m_x_buffer;
    int m_y_buffer;
};

#endif
