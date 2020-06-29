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
                return ARROW_UP;

                case SDLK_DOWN:
                return ARROW_DOWN;

                case SDLK_LEFT:
                return ARROW_LEFT;

                case SDLK_RIGHT:
                return ARROW_RIGHT;

                case SDLK_ESCAPE:
                return ESCAPE;

                case SDLK_F1:
                return F1;
            }
        }
    }
    return NONE;
}
