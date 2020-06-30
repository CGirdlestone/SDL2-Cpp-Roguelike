#include <stdio.h>
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "Console.h"
#include "Tile.h"




Console::Console(int width, int height, char* title, char* path, int fontSize)
{
    //ctor
    m_width = width;
    m_height = height;
    m_title = title;
    m_root = nullptr;
    m_rootSurface = nullptr;
    m_renderer = nullptr;
    m_font = nullptr;
    m_texture = nullptr;
    m_wall = nullptr;
    m_space = nullptr;
    m_at = nullptr;
    m_tileSize = fontSize;
    init(path, fontSize);
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

    delete m_font;
    m_font = nullptr;

    delete m_wall;
    m_wall = nullptr;

    delete m_space;
    m_space = nullptr;

    delete m_at;
    m_at = nullptr;

}

bool Console::init(char* path, int fontSize)
{

    if (SDL_Init(SDL_INIT_VIDEO) < 0){
        printf("SDL Coult not initialise! SDL_Error: %s\n", SDL_GetError());
        return false;
    }

    /*if(!initFont(path, fontSize)){
        return false;
    }*/

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
    m_root = SDL_CreateWindow(m_title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_width*m_tileSize, m_height*m_tileSize, SDL_WINDOW_SHOWN);
    if (m_root == nullptr){
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return false;
    } else {
        std::cout << "Window created!" << std::endl;
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
        SDL_SetRenderDrawColor(m_renderer, 0x00, 0x00, 0x00, 0xFF);
        std::cout << "Renderer created!" << std::endl;
        return true;
    }
}

bool Console::initFont(char* path, int fontSize)
{
    if (TTF_Init() == -1){
        printf("Failed to initialise SDL_ttf! SDL_ttf Error: %s\n", TTF_GetError());
        return false;
    }

    setFont(path, fontSize);
    return true;
}

bool Console::initImage()
{
    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags)){
        printf("Failed to initialise SDL_Image! SDL_image Error: %s\n", IMG_GetError());
        return false;
    }
    std::cout << "Init Image!" << std::endl;
    return true;
}

bool Console::setFont(char* path, int fontSize)
{
    m_fontSize = fontSize;
    m_font = TTF_OpenFont(path, m_fontSize);

    if (m_font == nullptr){
        printf("Failed to load font! SDL_TTF_Error: %s\n", TTF_GetError());
        return false;
    }

    TTF_SizeText(m_font, "#", &m_textWidth, &m_textHeight);
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
    std::cout << "Loaded Texture!" << std::endl;
    return true;
  }
}

void Console::createTiles()
{
    m_wall = new Tile(30, 0, 10);
    m_space = new Tile(0, 0, 10);
    m_at = new Tile(0, 10 ,10);
}

void Console::render(char* c, int x, int y)
{

    SDL_Rect dstrect;
    dstrect.x = x  * m_tileSize;
    dstrect.y = y * m_tileSize;
    dstrect.w = m_tileSize;
    dstrect.h = m_tileSize;

    SDL_Rect srcrect;
    srcrect.w = m_tileSize;
    srcrect.h = m_tileSize;

    if ((*c) == '#'){
        srcrect.x = m_wall->m_x;
        srcrect.y = m_wall->m_y;
    } else if ((*c) == '.'){
        srcrect.x = m_space->m_x;
        srcrect.y = m_space->m_y;
    } else if ((*c) == '@'){
        srcrect.x = m_at->m_x;
        srcrect.y = m_at->m_y;
    }

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
      SDL_SetWindowFullscreen(m_root, SDL_WINDOW_FULLSCREEN);
    } else if (m_fullscreen){
      m_fullscreen = 0;
      SDL_SetWindowFullscreen(m_root, 0);
    }
}

void Console::closeSDL()
{
    SDL_Quit();
    TTF_Quit();
    IMG_Quit();
}
