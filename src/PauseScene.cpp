
#include "PauseScene.h"
#include "SDL2/SDL.h"
#include "Renderer.h"
#include "KeyPressSurfaces.h"
#include "EventManager.h"
#include "Events.h"
#include "EventTypes.h"
#include "SceneTypes.h"


PauseScene::PauseScene(EventManager *eventManager, Renderer *renderer, Camera *camera, DungeonGenerator *dungeon, std::map<int, GameObject*> *actors, MessageLog *messageLog):
m_eventManager(eventManager), m_renderer(renderer), m_camera(camera), m_dungeon(dungeon), m_entities(actors), m_messageLog(messageLog), m_i(0)
{

}

PauseScene::~PauseScene()
{

}

enum KeyPressSurfaces PauseScene::getEvent(SDL_Event *e)
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

				case SDLK_ESCAPE:
				return ESCAPE;
      }
    }
  }
  return NONE;
}

void PauseScene::handleInput(KeyPressSurfaces keyPress)
{
  if (keyPress == ESCAPE){
		m_eventManager->pushEvent(PopScene(1));
	} else if (keyPress == MENUUP){
    m_i = m_i - 1 < 0 ? 1 : m_i - 1;
  } else if (keyPress == MENUDOWN){
    m_i = m_i + 1 > 1 ? 0 : m_i + 1;
  } else if (keyPress == PRESS and m_i == 0){
    m_eventManager->pushEvent(PopScene(1));
  } else if (keyPress == PRESS and m_i == 1){
    m_eventManager->pushEvent(QuitEvent());
	}
}

void PauseScene::render()
{
  m_renderer->drawPauseMenu(m_i, m_camera, m_dungeon, m_entities, m_messageLog);
}

void PauseScene::update(Uint32)
{

}

void PauseScene::onTick()
{

}
