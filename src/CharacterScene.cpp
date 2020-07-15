
#include <map>
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
#include "Slots.h"

CharacterScene::CharacterScene(EventManager *eventManager, Renderer *renderer, std::map<int, GameObject*> *entities):
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

							case SDLK_e:
							return DOFF;
							
							case SDLK_i:
							return BAG;
          }
      }
  }
  return NONE;
}

void CharacterScene::handleInput(KeyPressSurfaces keyPress)
{
	int inventorySize = m_entities->at(0)->inventory->inventory.size();
	GameObject* item = m_entities->at(0)->body->slots[static_cast<EquipSlots>(m_index)];

  if (keyPress == ESCAPE){
    m_eventManager->pushEvent(PopScene(1));
  }else if (keyPress == NORTH){
		m_index = m_index - 1 < 0 ? 6 - 1 : m_index - 1;
	} else if (keyPress == SOUTH){
		m_index = m_index + 1 >= 6 ? 0 : m_index + 1;
	} else if (keyPress == DOFF){
		//TODO
		if (item != nullptr){
			m_eventManager->pushEvent(UnequipEvent(0, item->m_uid, m_index));
		}
	} else if (keyPress == BAG){
		m_eventManager->pushEvent(PopScene(1));
		m_eventManager->pushEvent(PushScene(INVENTORY));
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
