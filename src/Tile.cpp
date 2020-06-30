

#include "SDL2/SDL.h";

#include "Tile.h"

Tile::Tile(int x, int y, int tileSize){
    m_x = x * tileSize;
    m_y = y * tileSize;
    m_tileSize = tileSize;
}

Tile::~Tile(){

}
