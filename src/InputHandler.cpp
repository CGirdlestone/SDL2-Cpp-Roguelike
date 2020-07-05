#include <SDL2/SDL.h>

#include "InputHandler.h"
#include "KeyPressSurfaces.h"

InputHandler::InputHandler()
{
    //ctor
}

InputHandler::~InputHandler()
{
    //dtor
}

enum KeyPressSurfaces InputHandler::getEvent(SDL_Event* e){
    while(SDL_PollEvent(e)){
        if (e->type == SDL_QUIT){
            return ESCAPE;
        } else if (e->type == SDL_KEYDOWN){
            switch(e->key.keysym.sym){
                case SDLK_UP:
                return NORTH;

                case SDLK_DOWN:
                return SOUTH;

                case SDLK_LEFT:
                return WEST;

                case SDLK_RIGHT:
                return EAST;

                case SDLK_KP_1:
                return SOUTHWEST;

                case SDLK_KP_2:
                return SOUTH;

                case SDLK_KP_3:
                return SOUTHEAST;

                case SDLK_KP_4:
                return WEST;

                case SDLK_KP_5:
                return WAIT;

                case SDLK_KP_6:
                return EAST;

                case SDLK_KP_7:
                return NORTHWEST;

                case SDLK_KP_8:
                return NORTH;

                case SDLK_KP_9:
                return NORTHEAST;

                case SDLK_ESCAPE:
                return ESCAPE;

                case SDLK_F1:
                return F1;
            }
        }
    }
    return NONE;
}
