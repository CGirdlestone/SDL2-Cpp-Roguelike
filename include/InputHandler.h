#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H

#include "KeyPressSurfaces.h"

class InputHandler
{
    public:
        InputHandler();
        virtual ~InputHandler();

        enum KeyPressSurfaces getEvent(SDL_Event* e);

    protected:

    private:
};

#endif // INPUTHANDLER_H
