#include <fstream>
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
	std::ifstream file("save.txt");
	if (file.good()){
		hasSaveFile = true;
		m_options = 3;
	} else {
		hasSaveFile = false;
		m_options = 2;
	}
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
  
	} else if (keyPress == MENUUP){
    m_i = m_i - 1 < 0 ? m_options - 1 : m_i - 1;
  } else if (keyPress == MENUDOWN){
    m_i = m_i + 1 > m_options - 1 ? 0 : m_i + 1;
  } else if (keyPress == PRESS){
		if (m_options == 2 && m_i == 1){
    	m_eventManager->pushEvent(QuitEvent());
		} else if ((m_options == 2 && m_i == 0) || (m_options == 3 && m_i == 1)){
    	PushScene transition = PushScene(GAMESCENE);
    	m_eventManager->pushEvent(transition);
		} else if (m_options == 3 && m_i == 0){
			// load game
			m_eventManager->pushEvent(LoadEvent());
		}
  }
}


void StartScene::render()
{
  m_renderer->drawStartMenu(m_i, m_options);
}

void StartScene::update(Uint32)
{

}

void StartScene::onTick()
{

}
