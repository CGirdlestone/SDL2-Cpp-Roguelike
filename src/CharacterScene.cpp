

#include "StartScene.h"
#include "SDL2/SDL.h"
#include "Renderer.h"
#include "KeyPressSurfaces.h"
#include "Pathfind.h"
#include "EventManager.h"
#include "Events.h"
#include "EventTypes.h"
#include "SceneTypes.h"
#include "CharacterScene.h"


CharacterScene::CharacterScene(EventManager *eventManager, Renderer *renderer, std::vector<GameObject*> *entities):
m_eventManager(eventManager), m_renderer(renderer), m_entities(entities)
{
	m_index = 0;
}

CharacterScene::~CharacterScene()
{

}

enum KeyPressSurfaces CharacterScene::getEvent(SDL_Event *e)
{
  while(SDL_PollEvent(e)){
      if (e->type == SDL_QUIT){
          return ESCAPE;
      } else if (e->type == SDL_KEYDOWN){
          switch(e->key.keysym.sym){
              case SDLK_UP:
              return NORTH;

              case SDLK_DOWN:
              return SOUTH;

              case SDLK_KP_2:
              return SOUTH;

							case SDLK_KP_8:
							return NORTH;

              case SDLK_c:
              return ESCAPE;

							case SDLK_ESCAPE:
							return ESCAPE;
          }
      }
  }
  return NONE;
}

void CharacterScene::handleInput(KeyPressSurfaces keyPress)
{
	int inventorySize = m_entities->at(0)->inventory->inventory.size();
	int x = m_entities->at(0)->position->x;
	int y = m_entities->at(0)->position->y;

  if (keyPress == ESCAPE){
    m_eventManager->pushEvent(PopScene(1));
  }else if (keyPress == NORTH){
		m_index = m_index - 1 < 0 ? inventorySize - 1 : m_index - 1;
	} else if (keyPress == SOUTH){
		m_index = m_index + 1 >= inventorySize ? 0 : m_index + 1;
	}
}


void CharacterScene::render()
{
	m_renderer->drawCharacterScene(m_entities, m_index);  
}

void CharacterScene::update(Uint32 dt)
{

}

void CharacterScene::onTick()
{

}
