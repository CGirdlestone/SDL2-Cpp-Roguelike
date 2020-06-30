#ifndef MESSAGE_H
#define MESSAGE_H

#include <string>
#include "SDL2/SDL.h"

class Message
{
public:
      Message(std::string msg, SDL_Color colour);
      ~Message();
      std::string m_msg;
      SDL_Color m_colour;
};

#endif
