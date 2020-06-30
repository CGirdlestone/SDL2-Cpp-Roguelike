#ifndef TILE_H
#define TILE_H

#include "SDL2/SDL.h"

class Tile
{
    public:
        Tile(int x, int y, int tileSize);
        virtual ~Tile();

        int m_x;
        int m_y;
        int m_tileSize;

    protected:

    private:

};


#endif
