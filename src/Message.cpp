
#include <string>
#include "SDL2/SDL.h"

#include "Message.h"

Message::Message(std::string msg, SDL_Color colour)
{
    m_msg = msg;
    m_colour = colour;
}

Message::~Message()
{

}
