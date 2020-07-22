#include <stdio.h>
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Console.h"
#include "Tile.h"




Console::Console(int width, int height, const char* title, char* path, int tileSize)
{
    //ctor
    m_width = width;
    m_height = height;
    m_title = title;
    m_root = nullptr;
    m_rootSurface = nullptr;
    m_renderer = nullptr;
    m_texture = nullptr;
    m_tileSize = tileSize;
    m_xBuffer = 20;
    m_yBuffer = 10;
    init(path);
}

Console::~Console()
{
    //dtor
    SDL_DestroyWindow(m_root);
    m_root = nullptr;

    SDL_DestroyRenderer(m_renderer);
    m_renderer = nullptr;

    SDL_FreeSurface(m_rootSurface);
    m_rootSurface = nullptr;

    SDL_DestroyTexture(m_texture);
    m_texture = nullptr;
}

bool Console::init(char* path)
{

    if (SDL_Init(SDL_INIT_VIDEO) < 0){
        printf("SDL Coult not initialise! SDL_Error: %s\n", SDL_GetError());
        return false;
    }

    if(!createWindow()){
        return false;
    }

    if(!createRenderer()){
        return false;
    }

    if(!initImage()){
        return false;
    }

    loadMedia(path);
    createTiles();

    m_fullscreen = 0;

    return true;
}

bool Console::createWindow()
{
    m_root = SDL_CreateWindow(m_title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, (m_width+m_xBuffer)*m_tileSize, (m_height+m_yBuffer)*m_tileSize, SDL_WINDOW_SHOWN);
    if (m_root == nullptr){
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return false;
    } else {
        return true;
    }
}

bool Console::createRenderer()
{
    m_renderer = SDL_CreateRenderer(m_root, -1, SDL_RENDERER_ACCELERATED);
    if (m_renderer == nullptr){
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        return false;
    } else {
        SDL_SetRenderDrawColor(m_renderer, 0x00, 0x00, 0x00, 0x00);
        return true;
    }
}

bool Console::initImage()
{
    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags)){
        printf("Failed to initialise SDL_Image! SDL_image Error: %s\n", IMG_GetError());
        return false;
    }
    return true;
}

bool Console::loadMedia(char* path)
{

  SDL_Surface *loadedSurface = IMG_Load(path);

  if(loadedSurface == nullptr){
    printf("Failed to load image! SDL_image Error: %s\n", IMG_GetError());
    return false;
  } else {
    m_texture = SDL_CreateTextureFromSurface(m_renderer, loadedSurface);
    SDL_FreeSurface(loadedSurface);
    loadedSurface = nullptr;
    return true;
  }
}

void Console::fillBackgroundTile(int x, int y, SDL_Color colour)
{
	SDL_Rect rect;
	rect.x = x * m_tileSize;
	rect.y = y * m_tileSize;
	rect.w = m_tileSize;
	rect.h = m_tileSize;

	SDL_SetRenderDrawColor(m_renderer, colour.r, colour.g, colour.b, 128);
	SDL_SetRenderDrawBlendMode(m_renderer, SDL_BLENDMODE_BLEND);
	SDL_RenderFillRect(m_renderer, &rect);
	SDL_SetRenderDrawColor(m_renderer, 0x00, 0x00, 0x00, 0x00);
}

void Console::createTiles()
{
    int textureSize = m_tileSize * m_tileSize;

    for(int i = 0; i < textureSize; i++){
        m_glyphs.push_back(Tile(i%m_tileSize, i/m_tileSize, m_tileSize));
    }
}

void Console::render(char* c, int x, int y, SDL_Color colour){
    int i = static_cast<int>((*c));

    SDL_Rect dstrect;
    dstrect.x = x  * m_tileSize;
    dstrect.y = y * m_tileSize;
    dstrect.w = m_tileSize;
    dstrect.h = m_tileSize;

    SDL_Rect srcrect;
    srcrect.w = m_tileSize;
    srcrect.h = m_tileSize;

    srcrect.x = m_glyphs.at(i).m_x;
    srcrect.y = m_glyphs.at(i).m_y;

    SDL_SetTextureColorMod(m_texture, colour.r, colour.g, colour.b);
    SDL_RenderCopy(m_renderer, m_texture, &srcrect, &dstrect);
}

void Console::render(int i, int x, int y, SDL_Color colour){

    SDL_Rect dstrect;
    dstrect.x = x  * m_tileSize;
    dstrect.y = y * m_tileSize;
    dstrect.w = m_tileSize;
    dstrect.h = m_tileSize;

    SDL_Rect srcrect;
    srcrect.w = m_tileSize;
    srcrect.h = m_tileSize;

    srcrect.x = m_glyphs.at(i).m_x;
    srcrect.y = m_glyphs.at(i).m_y;

    SDL_SetTextureColorMod(m_texture, colour.r, colour.g, colour.b);
    SDL_RenderCopy(m_renderer, m_texture, &srcrect, &dstrect);
}

void Console::update()
{
    SDL_RenderPresent(m_renderer);
}

void Console::flush()
{
    SDL_RenderClear(m_renderer);
}

void Console::setFullscreen()
{
    if (!m_fullscreen){
      m_fullscreen = 1;
      SDL_SetWindowFullscreen(m_root, SDL_WINDOW_FULLSCREEN_DESKTOP);
    } else if (m_fullscreen){
      m_fullscreen = 0;
      SDL_SetWindowFullscreen(m_root, 0);
    }
}

void Console::closeSDL()
{
    SDL_Quit();
    IMG_Quit();
}
