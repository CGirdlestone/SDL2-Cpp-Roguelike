

#include "SDL2/SDL.h";

#include "Tile.h"

Tile::Tile(int x, int y, int tileSize){
    m_x = x;
    m_y = y;
    m_tileSize = tileSize;
}

Tile::~Tile(){

}
