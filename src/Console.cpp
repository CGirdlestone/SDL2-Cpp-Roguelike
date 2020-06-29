#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "Console.h"




Console::Console(int width, int height, char* title, char* path, int fontSize)
{
    //ctor
    m_width = width;
    m_height = height;
    m_title = title;
    m_backgroundColour = {30, 30, 30};
    m_root = nullptr;
    m_rootSurface = nullptr;
    m_renderer = nullptr;
    m_font = nullptr;
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

    delete m_font;
    m_font = nullptr;

}

bool Console::init(char* path, int fontSize){

    if (SDL_Init(SDL_INIT_VIDEO) < 0){
        printf("SDL Coult not initialise! SDL_Error: %s\n", SDL_GetError());
        return false;
    }

    if(!initFont(path, fontSize)){
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

    m_rootSurface = SDL_GetWindowSurface(m_root);
    setFont(path, fontSize);

    m_fullscreen = 0;

    return true;
}

bool Console::createWindow(){
    m_root = SDL_CreateWindow(m_title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_width*m_textWidth, m_height*m_textHeight, SDL_WINDOW_SHOWN);
    if (m_root == nullptr){
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return false;
    } else {
        return true;
    }
}

bool Console::createRenderer(){
    m_renderer = SDL_CreateRenderer(m_root, -1, SDL_RENDERER_ACCELERATED);
    if (m_renderer == nullptr){
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        return false;
    } else {
        SDL_SetRenderDrawColor(m_renderer, 0xFF, 0xFF, 0xFF,0xFF);
        return true;
    }
}

bool Console::initFont(char* path, int fontSize){
    if (TTF_Init() == -1){
        printf("Failed to initialise SDL_ttf! SDL_ttf Error: %s\n", TTF_GetError());
        return false;
    }

    setFont(path, fontSize);
    return true;
}

bool Console::initImage(){
    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags)){
        printf("Failed to initialise SDL_Image! SDL_image Error: %s\n", IMG_GetError());
        return false;
    }
    return true;
}

bool Console::setFont(char* path, int fontSize){
    m_fontSize = fontSize;
    m_font = TTF_OpenFont(path, m_fontSize);

    if (m_font == nullptr){
        printf("Failed to load font! SDL_TTF_Error: %s\n", TTF_GetError());
        return false;
    }

    TTF_SizeText(m_font, "#", &m_textWidth, &m_textHeight);
    return true;
}

void Console::render(char* c, int x, int y, SDL_Color colour){

    SDL_Surface *textSurface = TTF_RenderText_Solid(m_font, c, colour);

    //SDL_Surface *background = SDL_CreateRGBSurface(0, textSurface->w, textSurface->h, 8, 0, 0, 0, 0);
    //SDL_FillRect(background, nullptr, SDL_MapRGB(background->format, m_backgroundColour.r, m_backgroundColour.g, m_backgroundColour.b));

    SDL_Rect srcrect;
    srcrect.x = 0;
    srcrect.y = 0;
    srcrect.w = m_textWidth;
    srcrect.h = m_textHeight;

    SDL_Rect dstrect;
    dstrect.x = x * m_textWidth;
    dstrect.y = y * m_textHeight;
    dstrect.w = m_textWidth;
    dstrect.h = m_textHeight;

    //SDL_BlitSurface(background,  &srcrect, m_rootSurface, &dstrect);
    SDL_BlitSurface(textSurface, &srcrect, m_rootSurface, &dstrect);

    //SDL_FreeSurface(background);
    SDL_FreeSurface(textSurface);

}

void Console::setBackgroundColour(Uint8 r, Uint8 g, Uint8 b){
  m_backgroundColour = {r, g, b};
}

void Console::update(){
    SDL_UpdateWindowSurface(m_root);
}

void Console::flush(){
  SDL_Surface *blankSurface = SDL_GetWindowSurface(m_root);
  SDL_FillRect(blankSurface, nullptr, SDL_MapRGB(blankSurface->format, 48, 98, 48));
  SDL_BlitSurface(blankSurface, nullptr, m_rootSurface, nullptr);

  SDL_FreeSurface(blankSurface);
  blankSurface = nullptr;
}

void Console::setFullscreen(){
  if (!m_fullscreen){
    m_fullscreen = 1;
    SDL_SetWindowFullscreen(m_root, SDL_WINDOW_FULLSCREEN);
  } else if (m_fullscreen){
    m_fullscreen = 0;
    SDL_SetWindowFullscreen(m_root, 0);
  }
}

void Console::closeSDL(){
    SDL_Quit();
    TTF_Quit();
    IMG_Quit();
}
