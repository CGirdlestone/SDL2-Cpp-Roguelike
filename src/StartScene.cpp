
#include "StartScene.h"
#include "SDL2/SDL.h"
#include "Renderer.h"
#include "KeyPressSurfaces.h"
#include "EventManager.h"
#include "Events.h"
#include "EventTypes.h"
#include "SceneTypes.h"


StartScene::StartScene(EventManager *eventManager, Renderer *renderer):
m_eventManager(eventManager), m_renderer(renderer), m_i(0)
{

}

StartScene::~StartScene()
{

}

enum KeyPressSurfaces StartScene::getEvent(SDL_Event *e)
{
  while(SDL_PollEvent(e)){
    if (e->type == SDL_QUIT){
      return ESCAPE;
    } else if (e->type == SDL_KEYDOWN){
      switch(e->key.keysym.sym){
        case SDLK_UP:
        return MENUUP;

        case SDLK_DOWN:
        return MENUDOWN;

        case SDLK_RETURN:
        return PRESS;
      }
    }
  }
  return NONE;
}

void StartScene::handleInput(KeyPressSurfaces keyPress)
{
  if (keyPress == ESCAPE){
    //
  } else if (keyPress == MENUUP){
    m_i = m_i - 1 < 0 ? 1 : m_i - 1;
  } else if (keyPress == MENUDOWN){
    m_i = m_i + 1 > 1 ? 0 : m_i + 1;
  } else if (keyPress == PRESS and m_i == 0){
    //
    PushScene transition = PushScene(GAMESCENE);
    m_eventManager->pushEvent(transition);
  }else if (keyPress == PRESS and m_i == 1){
    m_eventManager->pushEvent(QuitEvent());
  }
}


void StartScene::render()
{
  m_renderer->drawStartMenu(m_i);
}

void StartScene::update(Uint32)
{

}

void StartScene::onTick()
{

}
